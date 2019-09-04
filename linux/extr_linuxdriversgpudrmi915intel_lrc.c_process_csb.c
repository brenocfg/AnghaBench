#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  unsigned int u32 ;
struct intel_engine_execlists {unsigned int* csb_status; scalar_t__ csb_head; unsigned int const preempt_complete_status; int /*<<< orphan*/  active; int /*<<< orphan*/ * csb_write; struct execlist_port* port; } ;
struct intel_engine_cs {int /*<<< orphan*/  name; struct intel_engine_execlists execlists; } ;
struct TYPE_2__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {TYPE_1__ fence; int /*<<< orphan*/  global_seqno; } ;
struct execlist_port {unsigned int const context_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXECLISTS_ACTIVE_HWACK ; 
 int /*<<< orphan*/  EXECLISTS_ACTIVE_PREEMPT ; 
 int /*<<< orphan*/  EXECLISTS_ACTIVE_USER ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_DEBUG_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ GEN8_CSB_ENTRIES ; 
 unsigned int GEN8_CTX_STATUS_ACTIVE_IDLE ; 
 unsigned int GEN8_CTX_STATUS_COMPLETE ; 
 unsigned int GEN8_CTX_STATUS_COMPLETED_MASK ; 
 unsigned int GEN8_CTX_STATUS_ELEMENT_SWITCH ; 
 unsigned int GEN8_CTX_STATUS_IDLE_ACTIVE ; 
 unsigned int GEN8_CTX_STATUS_PREEMPTED ; 
 int /*<<< orphan*/  INTEL_CONTEXT_SCHEDULE_OUT ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_preempt_context (struct intel_engine_execlists* const) ; 
 int /*<<< orphan*/  execlists_clear_active (struct intel_engine_execlists* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execlists_context_schedule_out (struct i915_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ execlists_is_active (struct intel_engine_execlists* const,int /*<<< orphan*/ ) ; 
 struct execlist_port* execlists_port_complete (struct intel_engine_execlists* const,struct execlist_port*) ; 
 int /*<<< orphan*/  execlists_set_active (struct intel_engine_execlists* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execlists_user_begin (struct intel_engine_execlists* const,struct execlist_port*) ; 
 int /*<<< orphan*/  execlists_user_end (struct intel_engine_execlists* const) ; 
 int /*<<< orphan*/  i915_request_completed (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (struct intel_engine_cs*) ; 
 scalar_t__ port_isset (struct execlist_port*) ; 
 int /*<<< orphan*/  port_pack (struct i915_request*,unsigned int) ; 
 int /*<<< orphan*/  port_set (struct execlist_port*,int /*<<< orphan*/ ) ; 
 struct i915_request* port_unpack (struct execlist_port*,unsigned int*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  rq_prio (struct i915_request*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void process_csb(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;
	struct execlist_port *port = execlists->port;
	const u32 * const buf = execlists->csb_status;
	u8 head, tail;

	/*
	 * Note that csb_write, csb_status may be either in HWSP or mmio.
	 * When reading from the csb_write mmio register, we have to be
	 * careful to only use the GEN8_CSB_WRITE_PTR portion, which is
	 * the low 4bits. As it happens we know the next 4bits are always
	 * zero and so we can simply masked off the low u8 of the register
	 * and treat it identically to reading from the HWSP (without having
	 * to use explicit shifting and masking, and probably bifurcating
	 * the code to handle the legacy mmio read).
	 */
	head = execlists->csb_head;
	tail = READ_ONCE(*execlists->csb_write);
	GEM_TRACE("%s cs-irq head=%d, tail=%d\n", engine->name, head, tail);
	if (unlikely(head == tail))
		return;

	/*
	 * Hopefully paired with a wmb() in HW!
	 *
	 * We must complete the read of the write pointer before any reads
	 * from the CSB, so that we do not see stale values. Without an rmb
	 * (lfence) the HW may speculatively perform the CSB[] reads *before*
	 * we perform the READ_ONCE(*csb_write).
	 */
	rmb();

	do {
		struct i915_request *rq;
		unsigned int status;
		unsigned int count;

		if (++head == GEN8_CSB_ENTRIES)
			head = 0;

		/*
		 * We are flying near dragons again.
		 *
		 * We hold a reference to the request in execlist_port[]
		 * but no more than that. We are operating in softirq
		 * context and so cannot hold any mutex or sleep. That
		 * prevents us stopping the requests we are processing
		 * in port[] from being retired simultaneously (the
		 * breadcrumb will be complete before we see the
		 * context-switch). As we only hold the reference to the
		 * request, any pointer chasing underneath the request
		 * is subject to a potential use-after-free. Thus we
		 * store all of the bookkeeping within port[] as
		 * required, and avoid using unguarded pointers beneath
		 * request itself. The same applies to the atomic
		 * status notifier.
		 */

		GEM_TRACE("%s csb[%d]: status=0x%08x:0x%08x, active=0x%x\n",
			  engine->name, head,
			  buf[2 * head + 0], buf[2 * head + 1],
			  execlists->active);

		status = buf[2 * head];
		if (status & (GEN8_CTX_STATUS_IDLE_ACTIVE |
			      GEN8_CTX_STATUS_PREEMPTED))
			execlists_set_active(execlists,
					     EXECLISTS_ACTIVE_HWACK);
		if (status & GEN8_CTX_STATUS_ACTIVE_IDLE)
			execlists_clear_active(execlists,
					       EXECLISTS_ACTIVE_HWACK);

		if (!(status & GEN8_CTX_STATUS_COMPLETED_MASK))
			continue;

		/* We should never get a COMPLETED | IDLE_ACTIVE! */
		GEM_BUG_ON(status & GEN8_CTX_STATUS_IDLE_ACTIVE);

		if (status & GEN8_CTX_STATUS_COMPLETE &&
		    buf[2*head + 1] == execlists->preempt_complete_status) {
			GEM_TRACE("%s preempt-idle\n", engine->name);
			complete_preempt_context(execlists);
			continue;
		}

		if (status & GEN8_CTX_STATUS_PREEMPTED &&
		    execlists_is_active(execlists,
					EXECLISTS_ACTIVE_PREEMPT))
			continue;

		GEM_BUG_ON(!execlists_is_active(execlists,
						EXECLISTS_ACTIVE_USER));

		rq = port_unpack(port, &count);
		GEM_TRACE("%s out[0]: ctx=%d.%d, global=%d (fence %llx:%d) (current %d), prio=%d\n",
			  engine->name,
			  port->context_id, count,
			  rq ? rq->global_seqno : 0,
			  rq ? rq->fence.context : 0,
			  rq ? rq->fence.seqno : 0,
			  intel_engine_get_seqno(engine),
			  rq ? rq_prio(rq) : 0);

		/* Check the context/desc id for this event matches */
		GEM_DEBUG_BUG_ON(buf[2 * head + 1] != port->context_id);

		GEM_BUG_ON(count == 0);
		if (--count == 0) {
			/*
			 * On the final event corresponding to the
			 * submission of this context, we expect either
			 * an element-switch event or a completion
			 * event (and on completion, the active-idle
			 * marker). No more preemptions, lite-restore
			 * or otherwise.
			 */
			GEM_BUG_ON(status & GEN8_CTX_STATUS_PREEMPTED);
			GEM_BUG_ON(port_isset(&port[1]) &&
				   !(status & GEN8_CTX_STATUS_ELEMENT_SWITCH));
			GEM_BUG_ON(!port_isset(&port[1]) &&
				   !(status & GEN8_CTX_STATUS_ACTIVE_IDLE));

			/*
			 * We rely on the hardware being strongly
			 * ordered, that the breadcrumb write is
			 * coherent (visible from the CPU) before the
			 * user interrupt and CSB is processed.
			 */
			GEM_BUG_ON(!i915_request_completed(rq));

			execlists_context_schedule_out(rq,
						       INTEL_CONTEXT_SCHEDULE_OUT);
			i915_request_put(rq);

			GEM_TRACE("%s completed ctx=%d\n",
				  engine->name, port->context_id);

			port = execlists_port_complete(execlists, port);
			if (port_isset(port))
				execlists_user_begin(execlists, port);
			else
				execlists_user_end(execlists);
		} else {
			port_set(port, port_pack(rq, count));
		}
	} while (head != tail);

	execlists->csb_head = head;
}