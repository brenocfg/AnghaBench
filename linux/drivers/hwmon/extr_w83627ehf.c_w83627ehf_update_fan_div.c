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
struct w83627ehf_data {int* fan_div; int has_fan; } ;

/* Variables and functions */
 int /*<<< orphan*/  W83627EHF_REG_DIODE ; 
 int /*<<< orphan*/  W83627EHF_REG_FANDIV1 ; 
 int /*<<< orphan*/  W83627EHF_REG_FANDIV2 ; 
 int /*<<< orphan*/  W83627EHF_REG_SMI_OVT ; 
 int /*<<< orphan*/  W83627EHF_REG_VBAT ; 
 int w83627ehf_read_value (struct w83627ehf_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w83627ehf_update_fan_div(struct w83627ehf_data *data)
{
	int i;

	i = w83627ehf_read_value(data, W83627EHF_REG_FANDIV1);
	data->fan_div[0] = (i >> 4) & 0x03;
	data->fan_div[1] = (i >> 6) & 0x03;
	i = w83627ehf_read_value(data, W83627EHF_REG_FANDIV2);
	data->fan_div[2] = (i >> 6) & 0x03;
	i = w83627ehf_read_value(data, W83627EHF_REG_VBAT);
	data->fan_div[0] |= (i >> 3) & 0x04;
	data->fan_div[1] |= (i >> 4) & 0x04;
	data->fan_div[2] |= (i >> 5) & 0x04;
	if (data->has_fan & ((1 << 3) | (1 << 4))) {
		i = w83627ehf_read_value(data, W83627EHF_REG_DIODE);
		data->fan_div[3] = i & 0x03;
		data->fan_div[4] = ((i >> 2) & 0x03)
				 | ((i >> 5) & 0x04);
	}
	if (data->has_fan & (1 << 3)) {
		i = w83627ehf_read_value(data, W83627EHF_REG_SMI_OVT);
		data->fan_div[3] |= (i >> 5) & 0x04;
	}
}