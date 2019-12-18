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
struct elm_info {int ecc_steps; } ;
struct elm_errorvec {int error_count; int* error_loc; int error_uncorrectable; scalar_t__ error_reported; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int ECC_CORRECTABLE_MASK ; 
 int ECC_ERROR_LOCATION_MASK ; 
 int ECC_NB_ERRORS_MASK ; 
 int ELM_ERROR_LOCATION_0 ; 
 int /*<<< orphan*/  ELM_IRQSTATUS ; 
 int ELM_LOCATION_STATUS ; 
 int ERROR_LOCATION_SIZE ; 
 int /*<<< orphan*/  elm_configure_page_mode (struct elm_info*,int,int) ; 
 int elm_read_reg (struct elm_info*,int) ; 
 int /*<<< orphan*/  elm_write_reg (struct elm_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elm_error_correction(struct elm_info *info,
		struct elm_errorvec *err_vec)
{
	int i, j, errors = 0;
	int offset;
	u32 reg_val;

	for (i = 0; i < info->ecc_steps; i++) {

		/* Check error reported */
		if (err_vec[i].error_reported) {
			offset = ELM_LOCATION_STATUS + ERROR_LOCATION_SIZE * i;
			reg_val = elm_read_reg(info, offset);

			/* Check correctable error or not */
			if (reg_val & ECC_CORRECTABLE_MASK) {
				offset = ELM_ERROR_LOCATION_0 +
					ERROR_LOCATION_SIZE * i;

				/* Read count of correctable errors */
				err_vec[i].error_count = reg_val &
					ECC_NB_ERRORS_MASK;

				/* Update the error locations in error vector */
				for (j = 0; j < err_vec[i].error_count; j++) {

					reg_val = elm_read_reg(info, offset);
					err_vec[i].error_loc[j] = reg_val &
						ECC_ERROR_LOCATION_MASK;

					/* Update error location register */
					offset += 4;
				}

				errors += err_vec[i].error_count;
			} else {
				err_vec[i].error_uncorrectable = true;
			}

			/* Clearing interrupts for processed error vectors */
			elm_write_reg(info, ELM_IRQSTATUS, BIT(i));

			/* Disable page mode */
			elm_configure_page_mode(info, i, false);
		}
	}
}