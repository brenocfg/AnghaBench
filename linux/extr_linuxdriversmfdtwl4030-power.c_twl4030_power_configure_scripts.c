#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct twl4030_power_data {int num; TYPE_1__** scripts; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 int load_twl4030_script (struct twl4030_power_data const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_start_script_address ; 

__attribute__((used)) static int
twl4030_power_configure_scripts(const struct twl4030_power_data *pdata)
{
	int err;
	int i;
	u8 address = twl4030_start_script_address;

	for (i = 0; i < pdata->num; i++) {
		err = load_twl4030_script(pdata, pdata->scripts[i], address);
		if (err)
			return err;
		address += pdata->scripts[i]->size;
	}

	return 0;
}