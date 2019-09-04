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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct elm_info {int /*<<< orphan*/  elm_completion; } ;
struct elm_errorvec {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELM_IRQENABLE ; 
 int /*<<< orphan*/  ELM_IRQSTATUS ; 
 int INTR_EN_PAGE_MASK ; 
 int INTR_STATUS_PAGE_VALID ; 
 struct elm_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  elm_error_correction (struct elm_info*,struct elm_errorvec*) ; 
 int /*<<< orphan*/  elm_load_syndrome (struct elm_info*,struct elm_errorvec*,int /*<<< orphan*/ *) ; 
 int elm_read_reg (struct elm_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elm_start_processing (struct elm_info*,struct elm_errorvec*) ; 
 int /*<<< orphan*/  elm_write_reg (struct elm_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void elm_decode_bch_error_page(struct device *dev, u8 *ecc_calc,
		struct elm_errorvec *err_vec)
{
	struct elm_info *info = dev_get_drvdata(dev);
	u32 reg_val;

	/* Enable page mode interrupt */
	reg_val = elm_read_reg(info, ELM_IRQSTATUS);
	elm_write_reg(info, ELM_IRQSTATUS, reg_val & INTR_STATUS_PAGE_VALID);
	elm_write_reg(info, ELM_IRQENABLE, INTR_EN_PAGE_MASK);

	/* Load valid ecc byte to syndrome fragment register */
	elm_load_syndrome(info, err_vec, ecc_calc);

	/* Enable syndrome processing for which syndrome fragment is updated */
	elm_start_processing(info, err_vec);

	/* Wait for ELM module to finish locating error correction */
	wait_for_completion(&info->elm_completion);

	/* Disable page mode interrupt */
	reg_val = elm_read_reg(info, ELM_IRQENABLE);
	elm_write_reg(info, ELM_IRQENABLE, reg_val & ~INTR_EN_PAGE_MASK);
	elm_error_correction(info, err_vec);
}