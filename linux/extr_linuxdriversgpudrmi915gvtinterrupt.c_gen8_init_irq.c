#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct intel_gvt_irq {TYPE_2__** info; TYPE_1__* events; int /*<<< orphan*/  irq_info_bitmap; } ;
struct intel_gvt {int /*<<< orphan*/  dev_priv; } ;
struct TYPE_15__ {size_t group; size_t* bit_to_event; } ;
struct TYPE_14__ {int bit; TYPE_2__* info; } ;

/* Variables and functions */
 size_t AUX_CHANNEL_A ; 
 size_t AUX_CHANNEL_B ; 
 size_t AUX_CHANNEL_C ; 
 size_t AUX_CHANNEL_D ; 
 size_t BCS_AS_CONTEXT_SWITCH ; 
 size_t BCS_MI_FLUSH_DW ; 
 size_t BCS_MI_USER_INTERRUPT ; 
 size_t CRT_HOTPLUG ; 
 size_t DP_A_HOTPLUG ; 
 size_t DP_B_HOTPLUG ; 
 size_t DP_C_HOTPLUG ; 
 size_t DP_D_HOTPLUG ; 
 size_t GMBUS ; 
 size_t GSE ; 
 scalar_t__ HAS_BSD2 (int /*<<< orphan*/ ) ; 
 size_t INTEL_GVT_IRQ_INFO_DE_MISC ; 
 size_t INTEL_GVT_IRQ_INFO_DE_PIPE_A ; 
 size_t INTEL_GVT_IRQ_INFO_DE_PIPE_B ; 
 size_t INTEL_GVT_IRQ_INFO_DE_PIPE_C ; 
 size_t INTEL_GVT_IRQ_INFO_DE_PORT ; 
 size_t INTEL_GVT_IRQ_INFO_GT0 ; 
 size_t INTEL_GVT_IRQ_INFO_GT1 ; 
 size_t INTEL_GVT_IRQ_INFO_GT2 ; 
 size_t INTEL_GVT_IRQ_INFO_GT3 ; 
 size_t INTEL_GVT_IRQ_INFO_MASTER ; 
 size_t INTEL_GVT_IRQ_INFO_PCH ; 
 size_t INTEL_GVT_IRQ_INFO_PCU ; 
 scalar_t__ IS_BROADWELL (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_BROXTON (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_KABYLAKE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_SKYLAKE (int /*<<< orphan*/ ) ; 
 size_t PCU_PCODE2DRIVER_MAILBOX ; 
 size_t PCU_THERMAL ; 
 size_t PIPE_A_VBLANK ; 
 size_t PIPE_B_VBLANK ; 
 size_t PIPE_C_VBLANK ; 
 size_t PRIMARY_A_FLIP_DONE ; 
 size_t PRIMARY_B_FLIP_DONE ; 
 size_t PRIMARY_C_FLIP_DONE ; 
 size_t RCS_AS_CONTEXT_SWITCH ; 
 size_t RCS_MI_USER_INTERRUPT ; 
 size_t RCS_PIPE_CONTROL ; 
 size_t SPRITE_A_FLIP_DONE ; 
 size_t SPRITE_B_FLIP_DONE ; 
 size_t SPRITE_C_FLIP_DONE ; 
 size_t VCS2_AS_CONTEXT_SWITCH ; 
 size_t VCS2_MI_FLUSH_DW ; 
 size_t VCS2_MI_USER_INTERRUPT ; 
 size_t VCS_AS_CONTEXT_SWITCH ; 
 size_t VCS_MI_FLUSH_DW ; 
 size_t VCS_MI_USER_INTERRUPT ; 
 size_t VECS_AS_CONTEXT_SWITCH ; 
 size_t VECS_MI_FLUSH_DW ; 
 size_t VECS_MI_USER_INTERRUPT ; 
 TYPE_2__ gen8_de_misc_info ; 
 TYPE_2__ gen8_de_pipe_a_info ; 
 TYPE_2__ gen8_de_pipe_b_info ; 
 TYPE_2__ gen8_de_pipe_c_info ; 
 TYPE_2__ gen8_de_port_info ; 
 TYPE_2__ gen8_gt0_info ; 
 TYPE_2__ gen8_gt1_info ; 
 TYPE_2__ gen8_gt2_info ; 
 TYPE_2__ gen8_gt3_info ; 
 TYPE_2__ gen8_master_info ; 
 TYPE_2__ gen8_pcu_info ; 
 TYPE_2__ gvt_base_pch_info ; 
 struct intel_gvt* irq_to_gvt (struct intel_gvt_irq*) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen8_init_irq(
		struct intel_gvt_irq *irq)
{
	struct intel_gvt *gvt = irq_to_gvt(irq);

#define SET_BIT_INFO(s, b, e, i)		\
	do {					\
		s->events[e].bit = b;		\
		s->events[e].info = s->info[i];	\
		s->info[i]->bit_to_event[b] = e;\
	} while (0)

#define SET_IRQ_GROUP(s, g, i) \
	do { \
		s->info[g] = i; \
		(i)->group = g; \
		set_bit(g, s->irq_info_bitmap); \
	} while (0)

	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_MASTER, &gen8_master_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_GT0, &gen8_gt0_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_GT1, &gen8_gt1_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_GT2, &gen8_gt2_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_GT3, &gen8_gt3_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_DE_PIPE_A, &gen8_de_pipe_a_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_DE_PIPE_B, &gen8_de_pipe_b_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_DE_PIPE_C, &gen8_de_pipe_c_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_DE_PORT, &gen8_de_port_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_DE_MISC, &gen8_de_misc_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_PCU, &gen8_pcu_info);
	SET_IRQ_GROUP(irq, INTEL_GVT_IRQ_INFO_PCH, &gvt_base_pch_info);

	/* GEN8 level 2 interrupts. */

	/* GEN8 interrupt GT0 events */
	SET_BIT_INFO(irq, 0, RCS_MI_USER_INTERRUPT, INTEL_GVT_IRQ_INFO_GT0);
	SET_BIT_INFO(irq, 4, RCS_PIPE_CONTROL, INTEL_GVT_IRQ_INFO_GT0);
	SET_BIT_INFO(irq, 8, RCS_AS_CONTEXT_SWITCH, INTEL_GVT_IRQ_INFO_GT0);

	SET_BIT_INFO(irq, 16, BCS_MI_USER_INTERRUPT, INTEL_GVT_IRQ_INFO_GT0);
	SET_BIT_INFO(irq, 20, BCS_MI_FLUSH_DW, INTEL_GVT_IRQ_INFO_GT0);
	SET_BIT_INFO(irq, 24, BCS_AS_CONTEXT_SWITCH, INTEL_GVT_IRQ_INFO_GT0);

	/* GEN8 interrupt GT1 events */
	SET_BIT_INFO(irq, 0, VCS_MI_USER_INTERRUPT, INTEL_GVT_IRQ_INFO_GT1);
	SET_BIT_INFO(irq, 4, VCS_MI_FLUSH_DW, INTEL_GVT_IRQ_INFO_GT1);
	SET_BIT_INFO(irq, 8, VCS_AS_CONTEXT_SWITCH, INTEL_GVT_IRQ_INFO_GT1);

	if (HAS_BSD2(gvt->dev_priv)) {
		SET_BIT_INFO(irq, 16, VCS2_MI_USER_INTERRUPT,
			INTEL_GVT_IRQ_INFO_GT1);
		SET_BIT_INFO(irq, 20, VCS2_MI_FLUSH_DW,
			INTEL_GVT_IRQ_INFO_GT1);
		SET_BIT_INFO(irq, 24, VCS2_AS_CONTEXT_SWITCH,
			INTEL_GVT_IRQ_INFO_GT1);
	}

	/* GEN8 interrupt GT3 events */
	SET_BIT_INFO(irq, 0, VECS_MI_USER_INTERRUPT, INTEL_GVT_IRQ_INFO_GT3);
	SET_BIT_INFO(irq, 4, VECS_MI_FLUSH_DW, INTEL_GVT_IRQ_INFO_GT3);
	SET_BIT_INFO(irq, 8, VECS_AS_CONTEXT_SWITCH, INTEL_GVT_IRQ_INFO_GT3);

	SET_BIT_INFO(irq, 0, PIPE_A_VBLANK, INTEL_GVT_IRQ_INFO_DE_PIPE_A);
	SET_BIT_INFO(irq, 0, PIPE_B_VBLANK, INTEL_GVT_IRQ_INFO_DE_PIPE_B);
	SET_BIT_INFO(irq, 0, PIPE_C_VBLANK, INTEL_GVT_IRQ_INFO_DE_PIPE_C);

	/* GEN8 interrupt DE PORT events */
	SET_BIT_INFO(irq, 0, AUX_CHANNEL_A, INTEL_GVT_IRQ_INFO_DE_PORT);
	SET_BIT_INFO(irq, 3, DP_A_HOTPLUG, INTEL_GVT_IRQ_INFO_DE_PORT);

	/* GEN8 interrupt DE MISC events */
	SET_BIT_INFO(irq, 0, GSE, INTEL_GVT_IRQ_INFO_DE_MISC);

	/* PCH events */
	SET_BIT_INFO(irq, 17, GMBUS, INTEL_GVT_IRQ_INFO_PCH);
	SET_BIT_INFO(irq, 19, CRT_HOTPLUG, INTEL_GVT_IRQ_INFO_PCH);
	SET_BIT_INFO(irq, 21, DP_B_HOTPLUG, INTEL_GVT_IRQ_INFO_PCH);
	SET_BIT_INFO(irq, 22, DP_C_HOTPLUG, INTEL_GVT_IRQ_INFO_PCH);
	SET_BIT_INFO(irq, 23, DP_D_HOTPLUG, INTEL_GVT_IRQ_INFO_PCH);

	if (IS_BROADWELL(gvt->dev_priv)) {
		SET_BIT_INFO(irq, 25, AUX_CHANNEL_B, INTEL_GVT_IRQ_INFO_PCH);
		SET_BIT_INFO(irq, 26, AUX_CHANNEL_C, INTEL_GVT_IRQ_INFO_PCH);
		SET_BIT_INFO(irq, 27, AUX_CHANNEL_D, INTEL_GVT_IRQ_INFO_PCH);

		SET_BIT_INFO(irq, 4, PRIMARY_A_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_A);
		SET_BIT_INFO(irq, 5, SPRITE_A_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_A);

		SET_BIT_INFO(irq, 4, PRIMARY_B_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_B);
		SET_BIT_INFO(irq, 5, SPRITE_B_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_B);

		SET_BIT_INFO(irq, 4, PRIMARY_C_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_C);
		SET_BIT_INFO(irq, 5, SPRITE_C_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_C);
	} else if (IS_SKYLAKE(gvt->dev_priv)
			|| IS_KABYLAKE(gvt->dev_priv)
			|| IS_BROXTON(gvt->dev_priv)) {
		SET_BIT_INFO(irq, 25, AUX_CHANNEL_B, INTEL_GVT_IRQ_INFO_DE_PORT);
		SET_BIT_INFO(irq, 26, AUX_CHANNEL_C, INTEL_GVT_IRQ_INFO_DE_PORT);
		SET_BIT_INFO(irq, 27, AUX_CHANNEL_D, INTEL_GVT_IRQ_INFO_DE_PORT);

		SET_BIT_INFO(irq, 3, PRIMARY_A_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_A);
		SET_BIT_INFO(irq, 3, PRIMARY_B_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_B);
		SET_BIT_INFO(irq, 3, PRIMARY_C_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_C);

		SET_BIT_INFO(irq, 4, SPRITE_A_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_A);
		SET_BIT_INFO(irq, 4, SPRITE_B_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_B);
		SET_BIT_INFO(irq, 4, SPRITE_C_FLIP_DONE, INTEL_GVT_IRQ_INFO_DE_PIPE_C);
	}

	/* GEN8 interrupt PCU events */
	SET_BIT_INFO(irq, 24, PCU_THERMAL, INTEL_GVT_IRQ_INFO_PCU);
	SET_BIT_INFO(irq, 25, PCU_PCODE2DRIVER_MAILBOX, INTEL_GVT_IRQ_INFO_PCU);
}