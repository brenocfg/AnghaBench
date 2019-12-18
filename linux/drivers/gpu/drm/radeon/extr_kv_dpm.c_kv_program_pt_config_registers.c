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
struct radeon_device {int dummy; } ;
struct kv_pt_config_reg {int offset; int type; int value; int shift; int mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int KV_CONFIGREG_CACHE ; 
#define  KV_CONFIGREG_DIDT_IND 129 
#define  KV_CONFIGREG_SMC_IND 128 
 int RREG32 (int) ; 
 int RREG32_DIDT (int) ; 
 int RREG32_SMC (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  WREG32_DIDT (int,int) ; 
 int /*<<< orphan*/  WREG32_SMC (int,int) ; 

__attribute__((used)) static int kv_program_pt_config_registers(struct radeon_device *rdev,
					  const struct kv_pt_config_reg *cac_config_regs)
{
	const struct kv_pt_config_reg *config_regs = cac_config_regs;
	u32 data;
	u32 cache = 0;

	if (config_regs == NULL)
		return -EINVAL;

	while (config_regs->offset != 0xFFFFFFFF) {
		if (config_regs->type == KV_CONFIGREG_CACHE) {
			cache |= ((config_regs->value << config_regs->shift) & config_regs->mask);
		} else {
			switch (config_regs->type) {
			case KV_CONFIGREG_SMC_IND:
				data = RREG32_SMC(config_regs->offset);
				break;
			case KV_CONFIGREG_DIDT_IND:
				data = RREG32_DIDT(config_regs->offset);
				break;
			default:
				data = RREG32(config_regs->offset << 2);
				break;
			}

			data &= ~config_regs->mask;
			data |= ((config_regs->value << config_regs->shift) & config_regs->mask);
			data |= cache;
			cache = 0;

			switch (config_regs->type) {
			case KV_CONFIGREG_SMC_IND:
				WREG32_SMC(config_regs->offset, data);
				break;
			case KV_CONFIGREG_DIDT_IND:
				WREG32_DIDT(config_regs->offset, data);
				break;
			default:
				WREG32(config_regs->offset << 2, data);
				break;
			}
		}
		config_regs++;
	}

	return 0;
}