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
struct w83627ehf_data {int /*<<< orphan*/ * reg_temp_config; int /*<<< orphan*/ * reg_temp_hyst; int /*<<< orphan*/ * reg_temp_over; int /*<<< orphan*/ * reg_temp; } ;

/* Variables and functions */
 int /*<<< orphan*/ * W83627EHF_REG_TEMP ; 
 int /*<<< orphan*/ * W83627EHF_REG_TEMP_CONFIG ; 
 int /*<<< orphan*/ * W83627EHF_REG_TEMP_HYST ; 
 int /*<<< orphan*/ * W83627EHF_REG_TEMP_OVER ; 

__attribute__((used)) static void
w83627ehf_set_temp_reg_ehf(struct w83627ehf_data *data, int n_temp)
{
	int i;

	for (i = 0; i < n_temp; i++) {
		data->reg_temp[i] = W83627EHF_REG_TEMP[i];
		data->reg_temp_over[i] = W83627EHF_REG_TEMP_OVER[i];
		data->reg_temp_hyst[i] = W83627EHF_REG_TEMP_HYST[i];
		data->reg_temp_config[i] = W83627EHF_REG_TEMP_CONFIG[i];
	}
}