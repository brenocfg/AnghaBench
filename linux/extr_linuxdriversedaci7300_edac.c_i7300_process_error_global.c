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
typedef  unsigned long u32 ;
struct mem_ctl_info {struct i7300_pvt* pvt_info; } ;
struct i7300_pvt {int /*<<< orphan*/  pci_dev_16_2_fsb_err_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FERR_GLOBAL_HI ; 
 int /*<<< orphan*/  FERR_GLOBAL_LO ; 
 char* GET_ERR_FROM_TABLE (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  KERN_EMERG ; 
 int ferr_global_hi_is_fatal (unsigned long) ; 
 int /*<<< orphan*/  ferr_global_hi_name ; 
 int ferr_global_lo_is_fatal (unsigned long) ; 
 int /*<<< orphan*/  ferr_global_lo_name ; 
 unsigned long find_first_bit (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i7300_mc_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static void i7300_process_error_global(struct mem_ctl_info *mci)
{
	struct i7300_pvt *pvt;
	u32 errnum, error_reg;
	unsigned long errors;
	const char *specific;
	bool is_fatal;

	pvt = mci->pvt_info;

	/* read in the 1st FATAL error register */
	pci_read_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
			      FERR_GLOBAL_HI, &error_reg);
	if (unlikely(error_reg)) {
		errors = error_reg;
		errnum = find_first_bit(&errors,
					ARRAY_SIZE(ferr_global_hi_name));
		specific = GET_ERR_FROM_TABLE(ferr_global_hi_name, errnum);
		is_fatal = ferr_global_hi_is_fatal(errnum);

		/* Clear the error bit */
		pci_write_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
				       FERR_GLOBAL_HI, error_reg);

		goto error_global;
	}

	pci_read_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
			      FERR_GLOBAL_LO, &error_reg);
	if (unlikely(error_reg)) {
		errors = error_reg;
		errnum = find_first_bit(&errors,
					ARRAY_SIZE(ferr_global_lo_name));
		specific = GET_ERR_FROM_TABLE(ferr_global_lo_name, errnum);
		is_fatal = ferr_global_lo_is_fatal(errnum);

		/* Clear the error bit */
		pci_write_config_dword(pvt->pci_dev_16_2_fsb_err_regs,
				       FERR_GLOBAL_LO, error_reg);

		goto error_global;
	}
	return;

error_global:
	i7300_mc_printk(mci, KERN_EMERG, "%s misc error: %s\n",
			is_fatal ? "Fatal" : "NOT fatal", specific);
}