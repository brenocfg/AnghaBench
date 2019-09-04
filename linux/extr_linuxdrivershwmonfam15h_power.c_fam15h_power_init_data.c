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
typedef  int u64 ;
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
struct fam15h_power_data {int base_tdp; int tdp_to_watts; int processor_pwr_watts; int max_cu_acc_power; int power_period; int /*<<< orphan*/  cpu_pwr_sample_ratio; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MSR_F15H_CU_MAX_PWR_ACCUMULATOR ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_PROCESSOR_TDP ; 
 int /*<<< orphan*/  REG_TDP_LIMIT3 ; 
 int /*<<< orphan*/  X86_FEATURE_ACC_POWER ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid_ecx (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int fam15h_power_init_attrs (struct pci_dev*,struct fam15h_power_data*) ; 
 int /*<<< orphan*/  pci_bus_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ rdmsrl_safe (int /*<<< orphan*/ ,int*) ; 
 int read_registers (struct fam15h_power_data*) ; 

__attribute__((used)) static int fam15h_power_init_data(struct pci_dev *f4,
				  struct fam15h_power_data *data)
{
	u32 val;
	u64 tmp;
	int ret;

	pci_read_config_dword(f4, REG_PROCESSOR_TDP, &val);
	data->base_tdp = val >> 16;
	tmp = val & 0xffff;

	pci_bus_read_config_dword(f4->bus, PCI_DEVFN(PCI_SLOT(f4->devfn), 5),
				  REG_TDP_LIMIT3, &val);

	data->tdp_to_watts = ((val & 0x3ff) << 6) | ((val >> 10) & 0x3f);
	tmp *= data->tdp_to_watts;

	/* result not allowed to be >= 256W */
	if ((tmp >> 16) >= 256)
		dev_warn(&f4->dev,
			 "Bogus value for ProcessorPwrWatts (processor_pwr_watts>=%u)\n",
			 (unsigned int) (tmp >> 16));

	/* convert to microWatt */
	data->processor_pwr_watts = (tmp * 15625) >> 10;

	ret = fam15h_power_init_attrs(f4, data);
	if (ret)
		return ret;


	/* CPUID Fn8000_0007:EDX[12] indicates to support accumulated power */
	if (!boot_cpu_has(X86_FEATURE_ACC_POWER))
		return 0;

	/*
	 * determine the ratio of the compute unit power accumulator
	 * sample period to the PTSC counter period by executing CPUID
	 * Fn8000_0007:ECX
	 */
	data->cpu_pwr_sample_ratio = cpuid_ecx(0x80000007);

	if (rdmsrl_safe(MSR_F15H_CU_MAX_PWR_ACCUMULATOR, &tmp)) {
		pr_err("Failed to read max compute unit power accumulator MSR\n");
		return -ENODEV;
	}

	data->max_cu_acc_power = tmp;

	/*
	 * Milliseconds are a reasonable interval for the measurement.
	 * But it shouldn't set too long here, because several seconds
	 * would cause the read function to hang. So set default
	 * interval as 10 ms.
	 */
	data->power_period = 10;

	return read_registers(data);
}