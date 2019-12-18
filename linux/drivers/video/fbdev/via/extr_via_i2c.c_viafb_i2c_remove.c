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
struct via_i2c_stuff {int /*<<< orphan*/  adapter; scalar_t__ is_active; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int VIAFB_NUM_PORTS ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct via_i2c_stuff* via_i2c_par ; 

__attribute__((used)) static int viafb_i2c_remove(struct platform_device *platdev)
{
	int i;

	for (i = 0; i < VIAFB_NUM_PORTS; i++) {
		struct via_i2c_stuff *i2c_stuff = &via_i2c_par[i];
		/*
		 * Only remove those entries in the array that we've
		 * actually used (and thus initialized algo_data)
		 */
		if (i2c_stuff->is_active)
			i2c_del_adapter(&i2c_stuff->adapter);
	}
	return 0;
}