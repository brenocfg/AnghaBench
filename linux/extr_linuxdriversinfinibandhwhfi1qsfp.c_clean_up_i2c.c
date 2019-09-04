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
struct hfi1_devdata {int dummy; } ;
struct hfi1_asic_data {int /*<<< orphan*/ * i2c_bus1; int /*<<< orphan*/ * i2c_bus0; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_i2c_bus (int /*<<< orphan*/ *) ; 

void clean_up_i2c(struct hfi1_devdata *dd, struct hfi1_asic_data *ad)
{
	if (!ad)
		return;
	clean_i2c_bus(ad->i2c_bus0);
	ad->i2c_bus0 = NULL;
	clean_i2c_bus(ad->i2c_bus1);
	ad->i2c_bus1 = NULL;
}