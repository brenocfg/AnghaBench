#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct intel_engine_execlists {scalar_t__ ctrl_reg; struct execlist_port* port; } ;
struct intel_engine_cs {int /*<<< orphan*/  name; TYPE_2__* i915; struct intel_engine_execlists execlists; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {TYPE_3__ fence; int /*<<< orphan*/  global_seqno; } ;
struct execlist_port {int /*<<< orphan*/  context_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  awake; } ;
struct TYPE_5__ {TYPE_1__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_CTRL_LOAD ; 
 int /*<<< orphan*/  EXECLISTS_ACTIVE_HWACK ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_DEBUG_EXEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execlists_clear_active (struct intel_engine_execlists*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execlists_context_schedule_in (struct i915_request*) ; 
 unsigned int execlists_num_ports (struct intel_engine_execlists*) ; 
 scalar_t__ execlists_update_context (struct i915_request*) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  port_pack (struct i915_request*,unsigned int) ; 
 int /*<<< orphan*/  port_set (struct execlist_port*,int /*<<< orphan*/ ) ; 
 struct i915_request* port_unpack (struct execlist_port*,unsigned int*) ; 
 int /*<<< orphan*/  rq_prio (struct i915_request*) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  write_desc (struct intel_engine_execlists*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void execlists_submit_ports(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists *execlists = &engine->execlists;
	struct execlist_port *port = execlists->port;
	unsigned int n;

	/*
	 * We can skip acquiring intel_runtime_pm_get() here as it was taken
	 * on our behalf by the request (see i915_gem_mark_busy()) and it will
	 * not be relinquished until the device is idle (see
	 * i915_gem_idle_work_handler()). As a precaution, we make sure
	 * that all ELSP are drained i.e. we have processed the CSB,
	 * before allowing ourselves to idle and calling intel_runtime_pm_put().
	 */
	GEM_BUG_ON(!engine->i915->gt.awake);

	/*
	 * ELSQ note: the submit queue is not cleared after being submitted
	 * to the HW so we need to make sure we always clean it up. This is
	 * currently ensured by the fact that we always write the same number
	 * of elsq entries, keep this in mind before changing the loop below.
	 */
	for (n = execlists_num_ports(execlists); n--; ) {
		struct i915_request *rq;
		unsigned int count;
		u64 desc;

		rq = port_unpack(&port[n], &count);
		if (rq) {
			GEM_BUG_ON(count > !n);
			if (!count++)
				execlists_context_schedule_in(rq);
			port_set(&port[n], port_pack(rq, count));
			desc = execlists_update_context(rq);
			GEM_DEBUG_EXEC(port[n].context_id = upper_32_bits(desc));

			GEM_TRACE("%s in[%d]:  ctx=%d.%d, global=%d (fence %llx:%d) (current %d), prio=%d\n",
				  engine->name, n,
				  port[n].context_id, count,
				  rq->global_seqno,
				  rq->fence.context, rq->fence.seqno,
				  intel_engine_get_seqno(engine),
				  rq_prio(rq));
		} else {
			GEM_BUG_ON(!n);
			desc = 0;
		}

		write_desc(execlists, desc, n);
	}

	/* we need to manually load the submit queue */
	if (execlists->ctrl_reg)
		writel(EL_CTRL_LOAD, execlists->ctrl_reg);

	execlists_clear_active(execlists, EXECLISTS_ACTIVE_HWACK);
}