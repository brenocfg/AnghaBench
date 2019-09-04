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
typedef  unsigned int u64 ;
typedef  unsigned int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  count; int /*<<< orphan*/  state; } ;
struct intel_engine_execlists {unsigned int active; int /*<<< orphan*/ * port; TYPE_2__ tasklet; int /*<<< orphan*/  csb_head; } ;
struct TYPE_4__ {unsigned int* page_addr; } ;
struct intel_engine_cs {scalar_t__ id; struct intel_engine_execlists execlists; struct drm_i915_private* i915; TYPE_1__ status_page; int /*<<< orphan*/  mmio_base; } ;
struct i915_request {TYPE_3__* ring; } ;
struct drm_printer {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  hdr ;
struct TYPE_6__ {int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCID ; 
 int /*<<< orphan*/  DMA_FADD_I8XX ; 
 unsigned int GEN8_CSB_ENTRIES ; 
 unsigned int GEN8_CSB_READ_PTR (unsigned int) ; 
 unsigned int GEN8_CSB_WRITE_PTR (unsigned int) ; 
 scalar_t__ HAS_EXECLISTS (struct drm_i915_private*) ; 
 scalar_t__ HAS_LEGACY_SEMAPHORES (struct drm_i915_private*) ; 
 scalar_t__ HAS_VEBOX (struct drm_i915_private*) ; 
 unsigned int HEAD_ADDR ; 
 size_t I915_HWS_CSB_BUF0_INDEX ; 
 unsigned int I915_READ (int /*<<< orphan*/ ) ; 
 unsigned int I915_READ64_2x32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int I915_READ_IMR (struct intel_engine_cs const*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IPEHR ; 
 int /*<<< orphan*/  IPEIR ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int,int) ; 
 int MODE_IDLE ; 
 scalar_t__ RCS ; 
 int /*<<< orphan*/  RING_CONTEXT_STATUS_BUF_HI (struct intel_engine_cs const*,unsigned int) ; 
 int /*<<< orphan*/  RING_CONTEXT_STATUS_BUF_LO (struct intel_engine_cs const*,unsigned int) ; 
 int /*<<< orphan*/  RING_CONTEXT_STATUS_PTR (struct intel_engine_cs const*) ; 
 int /*<<< orphan*/  RING_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_DMA_FADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_DMA_FADD_UDW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_EXECLIST_STATUS_HI (struct intel_engine_cs const*) ; 
 int /*<<< orphan*/  RING_EXECLIST_STATUS_LO (struct intel_engine_cs const*) ; 
 int /*<<< orphan*/  RING_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_IPEHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_IPEIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_MI_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_PP_DIR_BASE (struct intel_engine_cs const*) ; 
 int /*<<< orphan*/  RING_PP_DIR_BASE_READ (struct intel_engine_cs const*) ; 
 int /*<<< orphan*/  RING_PP_DIR_DCLV (struct intel_engine_cs const*) ; 
 int /*<<< orphan*/  RING_START (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_SYNC_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_SYNC_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_SYNC_2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_TAIL (int /*<<< orphan*/ ) ; 
 int RING_WAIT ; 
 int RING_WAIT_SEMAPHORE ; 
 unsigned int TAIL_ADDR ; 
 int /*<<< orphan*/  TASKLET_STATE_SCHED ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  enableddisabled (int) ; 
 unsigned int execlists_num_ports (struct intel_engine_execlists const* const) ; 
 int i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 unsigned int intel_engine_get_active_head (struct intel_engine_cs const*) ; 
 unsigned int intel_engine_get_last_batch_head (struct intel_engine_cs const*) ; 
 int /*<<< orphan*/  intel_hws_csb_write_index (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_read_status_page (struct intel_engine_cs const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (unsigned int) ; 
 struct i915_request* port_unpack (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  print_request (struct drm_printer*,struct i915_request*,char*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upper_32_bits (unsigned int) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_engine_print_registers(const struct intel_engine_cs *engine,
					 struct drm_printer *m)
{
	struct drm_i915_private *dev_priv = engine->i915;
	const struct intel_engine_execlists * const execlists =
		&engine->execlists;
	u64 addr;

	if (engine->id == RCS && IS_GEN(dev_priv, 4, 7))
		drm_printf(m, "\tCCID: 0x%08x\n", I915_READ(CCID));
	drm_printf(m, "\tRING_START: 0x%08x\n",
		   I915_READ(RING_START(engine->mmio_base)));
	drm_printf(m, "\tRING_HEAD:  0x%08x\n",
		   I915_READ(RING_HEAD(engine->mmio_base)) & HEAD_ADDR);
	drm_printf(m, "\tRING_TAIL:  0x%08x\n",
		   I915_READ(RING_TAIL(engine->mmio_base)) & TAIL_ADDR);
	drm_printf(m, "\tRING_CTL:   0x%08x%s\n",
		   I915_READ(RING_CTL(engine->mmio_base)),
		   I915_READ(RING_CTL(engine->mmio_base)) & (RING_WAIT | RING_WAIT_SEMAPHORE) ? " [waiting]" : "");
	if (INTEL_GEN(engine->i915) > 2) {
		drm_printf(m, "\tRING_MODE:  0x%08x%s\n",
			   I915_READ(RING_MI_MODE(engine->mmio_base)),
			   I915_READ(RING_MI_MODE(engine->mmio_base)) & (MODE_IDLE) ? " [idle]" : "");
	}

	if (INTEL_GEN(dev_priv) >= 6) {
		drm_printf(m, "\tRING_IMR: %08x\n", I915_READ_IMR(engine));
	}

	if (HAS_LEGACY_SEMAPHORES(dev_priv)) {
		drm_printf(m, "\tSYNC_0: 0x%08x\n",
			   I915_READ(RING_SYNC_0(engine->mmio_base)));
		drm_printf(m, "\tSYNC_1: 0x%08x\n",
			   I915_READ(RING_SYNC_1(engine->mmio_base)));
		if (HAS_VEBOX(dev_priv))
			drm_printf(m, "\tSYNC_2: 0x%08x\n",
				   I915_READ(RING_SYNC_2(engine->mmio_base)));
	}

	addr = intel_engine_get_active_head(engine);
	drm_printf(m, "\tACTHD:  0x%08x_%08x\n",
		   upper_32_bits(addr), lower_32_bits(addr));
	addr = intel_engine_get_last_batch_head(engine);
	drm_printf(m, "\tBBADDR: 0x%08x_%08x\n",
		   upper_32_bits(addr), lower_32_bits(addr));
	if (INTEL_GEN(dev_priv) >= 8)
		addr = I915_READ64_2x32(RING_DMA_FADD(engine->mmio_base),
					RING_DMA_FADD_UDW(engine->mmio_base));
	else if (INTEL_GEN(dev_priv) >= 4)
		addr = I915_READ(RING_DMA_FADD(engine->mmio_base));
	else
		addr = I915_READ(DMA_FADD_I8XX);
	drm_printf(m, "\tDMA_FADDR: 0x%08x_%08x\n",
		   upper_32_bits(addr), lower_32_bits(addr));
	if (INTEL_GEN(dev_priv) >= 4) {
		drm_printf(m, "\tIPEIR: 0x%08x\n",
			   I915_READ(RING_IPEIR(engine->mmio_base)));
		drm_printf(m, "\tIPEHR: 0x%08x\n",
			   I915_READ(RING_IPEHR(engine->mmio_base)));
	} else {
		drm_printf(m, "\tIPEIR: 0x%08x\n", I915_READ(IPEIR));
		drm_printf(m, "\tIPEHR: 0x%08x\n", I915_READ(IPEHR));
	}

	if (HAS_EXECLISTS(dev_priv)) {
		const u32 *hws = &engine->status_page.page_addr[I915_HWS_CSB_BUF0_INDEX];
		u32 ptr, read, write;
		unsigned int idx;

		drm_printf(m, "\tExeclist status: 0x%08x %08x\n",
			   I915_READ(RING_EXECLIST_STATUS_LO(engine)),
			   I915_READ(RING_EXECLIST_STATUS_HI(engine)));

		ptr = I915_READ(RING_CONTEXT_STATUS_PTR(engine));
		read = GEN8_CSB_READ_PTR(ptr);
		write = GEN8_CSB_WRITE_PTR(ptr);
		drm_printf(m, "\tExeclist CSB read %d [%d cached], write %d [%d from hws], tasklet queued? %s (%s)\n",
			   read, execlists->csb_head,
			   write,
			   intel_read_status_page(engine, intel_hws_csb_write_index(engine->i915)),
			   yesno(test_bit(TASKLET_STATE_SCHED,
					  &engine->execlists.tasklet.state)),
			   enableddisabled(!atomic_read(&engine->execlists.tasklet.count)));
		if (read >= GEN8_CSB_ENTRIES)
			read = 0;
		if (write >= GEN8_CSB_ENTRIES)
			write = 0;
		if (read > write)
			write += GEN8_CSB_ENTRIES;
		while (read < write) {
			idx = ++read % GEN8_CSB_ENTRIES;
			drm_printf(m, "\tExeclist CSB[%d]: 0x%08x [0x%08x in hwsp], context: %d [%d in hwsp]\n",
				   idx,
				   I915_READ(RING_CONTEXT_STATUS_BUF_LO(engine, idx)),
				   hws[idx * 2],
				   I915_READ(RING_CONTEXT_STATUS_BUF_HI(engine, idx)),
				   hws[idx * 2 + 1]);
		}

		rcu_read_lock();
		for (idx = 0; idx < execlists_num_ports(execlists); idx++) {
			struct i915_request *rq;
			unsigned int count;

			rq = port_unpack(&execlists->port[idx], &count);
			if (rq) {
				char hdr[80];

				snprintf(hdr, sizeof(hdr),
					 "\t\tELSP[%d] count=%d, ring->start=%08x, rq: ",
					 idx, count,
					 i915_ggtt_offset(rq->ring->vma));
				print_request(m, rq, hdr);
			} else {
				drm_printf(m, "\t\tELSP[%d] idle\n", idx);
			}
		}
		drm_printf(m, "\t\tHW active? 0x%x\n", execlists->active);
		rcu_read_unlock();
	} else if (INTEL_GEN(dev_priv) > 6) {
		drm_printf(m, "\tPP_DIR_BASE: 0x%08x\n",
			   I915_READ(RING_PP_DIR_BASE(engine)));
		drm_printf(m, "\tPP_DIR_BASE_READ: 0x%08x\n",
			   I915_READ(RING_PP_DIR_BASE_READ(engine)));
		drm_printf(m, "\tPP_DIR_DCLV: 0x%08x\n",
			   I915_READ(RING_PP_DIR_DCLV(engine)));
	}
}