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
struct nct6775_data {int* fan_div; int has_fan; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  nct6775_update_fan_div_common (struct nct6775_data*) ; 
 int /*<<< orphan*/  nct6775_write_fan_div_common (struct nct6775_data*,int) ; 

__attribute__((used)) static void nct6775_init_fan_div(struct nct6775_data *data)
{
	int i;

	nct6775_update_fan_div_common(data);
	/*
	 * For all fans, start with highest divider value if the divider
	 * register is not initialized. This ensures that we get a
	 * reading from the fan count register, even if it is not optimal.
	 * We'll compute a better divider later on.
	 */
	for (i = 0; i < ARRAY_SIZE(data->fan_div); i++) {
		if (!(data->has_fan & BIT(i)))
			continue;
		if (data->fan_div[i] == 0) {
			data->fan_div[i] = 7;
			nct6775_write_fan_div_common(data, i);
		}
	}
}