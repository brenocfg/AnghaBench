#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct si_cac_config_reg {int offset; int type; int mask; int value; int shift; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int RREG32 (int) ; 
 int RREG32_SMC (int) ; 
#define  SISLANDS_CACCONFIG_CGIND 128 
 int SMC_CG_IND_END ; 
 int /*<<< orphan*/  SMC_CG_IND_START ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  WREG32_SMC (int,int) ; 

__attribute__((used)) static int si_program_cac_config_registers(struct amdgpu_device *adev,
					   const struct si_cac_config_reg *cac_config_regs)
{
	const struct si_cac_config_reg *config_regs = cac_config_regs;
	u32 data = 0, offset;

	if (!config_regs)
		return -EINVAL;

	while (config_regs->offset != 0xFFFFFFFF) {
		switch (config_regs->type) {
		case SISLANDS_CACCONFIG_CGIND:
			offset = SMC_CG_IND_START + config_regs->offset;
			if (offset < SMC_CG_IND_END)
				data = RREG32_SMC(offset);
			break;
		default:
			data = RREG32(config_regs->offset);
			break;
		}

		data &= ~config_regs->mask;
		data |= ((config_regs->value << config_regs->shift) & config_regs->mask);

		switch (config_regs->type) {
		case SISLANDS_CACCONFIG_CGIND:
			offset = SMC_CG_IND_START + config_regs->offset;
			if (offset < SMC_CG_IND_END)
				WREG32_SMC(offset, data);
			break;
		default:
			WREG32(config_regs->offset, data);
			break;
		}
		config_regs++;
	}
	return 0;
}