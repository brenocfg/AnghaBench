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
typedef  int /*<<< orphan*/  u32 ;
struct elm_info {int ecc_steps; } ;
struct elm_errorvec {scalar_t__ error_reported; } ;

/* Variables and functions */
 int ELM_SYNDROME_FRAGMENT_6 ; 
 int /*<<< orphan*/  ELM_SYNDROME_VALID ; 
 int SYNDROME_FRAGMENT_REG_SIZE ; 
 int /*<<< orphan*/  elm_read_reg (struct elm_info*,int) ; 
 int /*<<< orphan*/  elm_write_reg (struct elm_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elm_start_processing(struct elm_info *info,
		struct elm_errorvec *err_vec)
{
	int i, offset;
	u32 reg_val;

	/*
	 * Set syndrome vector valid, so that ELM module
	 * will process it for vectors error is reported
	 */
	for (i = 0; i < info->ecc_steps; i++) {
		if (err_vec[i].error_reported) {
			offset = ELM_SYNDROME_FRAGMENT_6 +
				SYNDROME_FRAGMENT_REG_SIZE * i;
			reg_val = elm_read_reg(info, offset);
			reg_val |= ELM_SYNDROME_VALID;
			elm_write_reg(info, offset, reg_val);
		}
	}
}