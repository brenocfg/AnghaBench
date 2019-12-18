#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* rtl_attributes ; 
 TYPE_1__ rtl_subsys ; 

__attribute__((used)) static void rtl_teardown_sysfs(void) {
	int i;
	for (i = 0; rtl_attributes[i]; i ++)
		device_remove_file(rtl_subsys.dev_root, rtl_attributes[i]);
	bus_unregister(&rtl_subsys);
}