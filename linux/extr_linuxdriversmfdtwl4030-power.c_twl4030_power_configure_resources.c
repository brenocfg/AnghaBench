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
struct twl4030_resconfig {scalar_t__ resource; } ;
struct twl4030_power_data {struct twl4030_resconfig* board_config; struct twl4030_resconfig* resource_config; } ;

/* Variables and functions */
 int twl4030_configure_resource (struct twl4030_resconfig*) ; 
 int /*<<< orphan*/  twl4030_patch_rconfig (struct twl4030_resconfig*,struct twl4030_resconfig*) ; 

__attribute__((used)) static int
twl4030_power_configure_resources(const struct twl4030_power_data *pdata)
{
	struct twl4030_resconfig *resconfig = pdata->resource_config;
	struct twl4030_resconfig *boardconf = pdata->board_config;
	int err;

	if (resconfig) {
		if (boardconf)
			twl4030_patch_rconfig(resconfig, boardconf);

		while (resconfig->resource) {
			err = twl4030_configure_resource(resconfig);
			if (err)
				return err;
			resconfig++;
		}
	}

	return 0;
}