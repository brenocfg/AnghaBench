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
struct nct6775_data {int has_fan_min; scalar_t__ has_fan_div; int /*<<< orphan*/ * REG_FAN_MIN; int /*<<< orphan*/  fan_min; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  nct6775_init_fan_div (struct nct6775_data*) ; 
 int /*<<< orphan*/  nct6775_read_value (struct nct6775_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nct6775_write_value (struct nct6775_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nct6775_init_fan_common(struct device *dev,
				    struct nct6775_data *data)
{
	int i;
	u8 reg;

	if (data->has_fan_div)
		nct6775_init_fan_div(data);

	/*
	 * If fan_min is not set (0), set it to 0xff to disable it. This
	 * prevents the unnecessary warning when fanX_min is reported as 0.
	 */
	for (i = 0; i < ARRAY_SIZE(data->fan_min); i++) {
		if (data->has_fan_min & BIT(i)) {
			reg = nct6775_read_value(data, data->REG_FAN_MIN[i]);
			if (!reg)
				nct6775_write_value(data, data->REG_FAN_MIN[i],
						    data->has_fan_div ? 0xff
								      : 0xff1f);
		}
	}
}