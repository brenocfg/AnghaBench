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
typedef  int u8 ;
struct intel_soc_pmic {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ipc_in ;

/* Variables and functions */
 int BXTWC_DEVICE1_ADDR ; 
 int EINVAL ; 
 int /*<<< orphan*/  PMC_IPC_PMIC_ACCESS ; 
 int /*<<< orphan*/  PMC_IPC_PMIC_ACCESS_WRITE ; 
 unsigned int REG_ADDR_MASK ; 
 unsigned int REG_ADDR_SHIFT ; 
 unsigned int REG_OFFSET_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int intel_pmc_ipc_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regmap_ipc_byte_reg_write(void *context, unsigned int reg,
				       unsigned int val)
{
	int ret;
	int i2c_addr;
	u8 ipc_in[3];
	struct intel_soc_pmic *pmic = context;

	if (!pmic)
		return -EINVAL;

	if (reg & REG_ADDR_MASK)
		i2c_addr = (reg & REG_ADDR_MASK) >> REG_ADDR_SHIFT;
	else
		i2c_addr = BXTWC_DEVICE1_ADDR;

	reg &= REG_OFFSET_MASK;

	ipc_in[0] = reg;
	ipc_in[1] = i2c_addr;
	ipc_in[2] = val;
	ret = intel_pmc_ipc_command(PMC_IPC_PMIC_ACCESS,
			PMC_IPC_PMIC_ACCESS_WRITE,
			ipc_in, sizeof(ipc_in), NULL, 0);
	if (ret) {
		dev_err(pmic->dev, "Failed to write to PMIC\n");
		return ret;
	}

	return 0;
}