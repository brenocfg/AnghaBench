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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_error_state_buf {int /*<<< orphan*/  i915; } ;
struct TYPE_6__ {int gfx_mode; int pp_dir_base; int /*<<< orphan*/ * pdp; } ;
struct drm_i915_error_engine {int start; int ctl; int mode; int hws; int acthd; int ipeir; int ipehr; int bbaddr; int bbstate; int instps; int instpm; int rc_psmi; int fault_reg; int cpu_ring_head; int cpu_ring_tail; unsigned long const hangcheck_timestamp; int reset_count; int num_ports; int /*<<< orphan*/  context; int /*<<< orphan*/ * execlist; TYPE_3__ vm_info; scalar_t__ faddr; TYPE_2__* batchbuffer; int /*<<< orphan*/  rq_tail; int /*<<< orphan*/  rq_post; int /*<<< orphan*/  tail; int /*<<< orphan*/  rq_head; int /*<<< orphan*/  head; int /*<<< orphan*/  idle; TYPE_1__* engine; } ;
struct TYPE_5__ {scalar_t__ gtt_size; scalar_t__ gtt_offset; } ;
struct TYPE_4__ {int name; } ;

/* Variables and functions */
 scalar_t__ HAS_PPGTT (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_printf (struct drm_i915_error_state_buf*,char*,int,...) ; 
 int /*<<< orphan*/  error_print_context (struct drm_i915_error_state_buf*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_print_instdone (struct drm_i915_error_state_buf*,struct drm_i915_error_engine const*) ; 
 int /*<<< orphan*/  error_print_request (struct drm_i915_error_state_buf*,char*,int /*<<< orphan*/ *,unsigned long const) ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long const) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 
 int yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void error_print_engine(struct drm_i915_error_state_buf *m,
			       const struct drm_i915_error_engine *ee,
			       const unsigned long epoch)
{
	int n;

	err_printf(m, "%s command stream:\n", ee->engine->name);
	err_printf(m, "  IDLE?: %s\n", yesno(ee->idle));
	err_printf(m, "  START: 0x%08x\n", ee->start);
	err_printf(m, "  HEAD:  0x%08x [0x%08x]\n", ee->head, ee->rq_head);
	err_printf(m, "  TAIL:  0x%08x [0x%08x, 0x%08x]\n",
		   ee->tail, ee->rq_post, ee->rq_tail);
	err_printf(m, "  CTL:   0x%08x\n", ee->ctl);
	err_printf(m, "  MODE:  0x%08x\n", ee->mode);
	err_printf(m, "  HWS:   0x%08x\n", ee->hws);
	err_printf(m, "  ACTHD: 0x%08x %08x\n",
		   (u32)(ee->acthd>>32), (u32)ee->acthd);
	err_printf(m, "  IPEIR: 0x%08x\n", ee->ipeir);
	err_printf(m, "  IPEHR: 0x%08x\n", ee->ipehr);

	error_print_instdone(m, ee);

	if (ee->batchbuffer) {
		u64 start = ee->batchbuffer->gtt_offset;
		u64 end = start + ee->batchbuffer->gtt_size;

		err_printf(m, "  batch: [0x%08x_%08x, 0x%08x_%08x]\n",
			   upper_32_bits(start), lower_32_bits(start),
			   upper_32_bits(end), lower_32_bits(end));
	}
	if (INTEL_GEN(m->i915) >= 4) {
		err_printf(m, "  BBADDR: 0x%08x_%08x\n",
			   (u32)(ee->bbaddr>>32), (u32)ee->bbaddr);
		err_printf(m, "  BB_STATE: 0x%08x\n", ee->bbstate);
		err_printf(m, "  INSTPS: 0x%08x\n", ee->instps);
	}
	err_printf(m, "  INSTPM: 0x%08x\n", ee->instpm);
	err_printf(m, "  FADDR: 0x%08x %08x\n", upper_32_bits(ee->faddr),
		   lower_32_bits(ee->faddr));
	if (INTEL_GEN(m->i915) >= 6) {
		err_printf(m, "  RC PSMI: 0x%08x\n", ee->rc_psmi);
		err_printf(m, "  FAULT_REG: 0x%08x\n", ee->fault_reg);
	}
	if (HAS_PPGTT(m->i915)) {
		err_printf(m, "  GFX_MODE: 0x%08x\n", ee->vm_info.gfx_mode);

		if (INTEL_GEN(m->i915) >= 8) {
			int i;
			for (i = 0; i < 4; i++)
				err_printf(m, "  PDP%d: 0x%016llx\n",
					   i, ee->vm_info.pdp[i]);
		} else {
			err_printf(m, "  PP_DIR_BASE: 0x%08x\n",
				   ee->vm_info.pp_dir_base);
		}
	}
	err_printf(m, "  ring->head: 0x%08x\n", ee->cpu_ring_head);
	err_printf(m, "  ring->tail: 0x%08x\n", ee->cpu_ring_tail);
	err_printf(m, "  hangcheck timestamp: %dms (%lu%s)\n",
		   jiffies_to_msecs(ee->hangcheck_timestamp - epoch),
		   ee->hangcheck_timestamp,
		   ee->hangcheck_timestamp == epoch ? "; epoch" : "");
	err_printf(m, "  engine reset count: %u\n", ee->reset_count);

	for (n = 0; n < ee->num_ports; n++) {
		err_printf(m, "  ELSP[%d]:", n);
		error_print_request(m, " ", &ee->execlist[n], epoch);
	}

	error_print_context(m, "  Active context: ", &ee->context);
}