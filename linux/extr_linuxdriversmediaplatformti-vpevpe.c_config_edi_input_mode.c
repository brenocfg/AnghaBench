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
struct TYPE_2__ {struct vpe_mmr_adb* addr; } ;
struct vpe_ctx {int load_mmrs; TYPE_1__ mmr_adb; } ;

/* Variables and functions */
 int VPE_EDI_INP_MODE_MASK ; 
 int VPE_EDI_INP_MODE_SHIFT ; 
 int /*<<< orphan*/  write_field (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void config_edi_input_mode(struct vpe_ctx *ctx, int mode)
{
	struct vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	u32 *edi_config_reg = &mmr_adb->dei_regs[3];

	if (mode & 0x2)
		write_field(edi_config_reg, 1, 1, 2);	/* EDI_ENABLE_3D */

	if (mode & 0x3)
		write_field(edi_config_reg, 1, 1, 3);	/* EDI_CHROMA_3D  */

	write_field(edi_config_reg, mode, VPE_EDI_INP_MODE_MASK,
		VPE_EDI_INP_MODE_SHIFT);

	ctx->load_mmrs = true;
}