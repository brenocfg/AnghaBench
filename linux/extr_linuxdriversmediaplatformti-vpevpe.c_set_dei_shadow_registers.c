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
typedef  int /*<<< orphan*/  u32 ;
struct vpe_mmr_adb {int /*<<< orphan*/ * dei_regs; } ;
struct vpe_dei_regs {int /*<<< orphan*/  edi_lut_reg3; int /*<<< orphan*/  edi_lut_reg2; int /*<<< orphan*/  edi_lut_reg1; int /*<<< orphan*/  edi_lut_reg0; int /*<<< orphan*/  edi_config_reg; int /*<<< orphan*/  mdt_spacial_freq_thr_reg; } ;
struct TYPE_2__ {struct vpe_mmr_adb* addr; } ;
struct vpe_ctx {int load_mmrs; TYPE_1__ mmr_adb; } ;

/* Variables and functions */
 struct vpe_dei_regs dei_regs ; 

__attribute__((used)) static void set_dei_shadow_registers(struct vpe_ctx *ctx)
{
	struct vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	u32 *dei_mmr = &mmr_adb->dei_regs[0];
	const struct vpe_dei_regs *cur = &dei_regs;

	dei_mmr[2]  = cur->mdt_spacial_freq_thr_reg;
	dei_mmr[3]  = cur->edi_config_reg;
	dei_mmr[4]  = cur->edi_lut_reg0;
	dei_mmr[5]  = cur->edi_lut_reg1;
	dei_mmr[6]  = cur->edi_lut_reg2;
	dei_mmr[7]  = cur->edi_lut_reg3;

	ctx->load_mmrs = true;
}