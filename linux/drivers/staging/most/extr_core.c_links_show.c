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
struct show_links_data {char* buf; int /*<<< orphan*/  offs; } ;
struct device_driver {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct show_links_data*,int /*<<< orphan*/ ) ; 
 TYPE_1__ mc ; 
 int /*<<< orphan*/  print_links ; 

__attribute__((used)) static ssize_t links_show(struct device_driver *drv, char *buf)
{
	struct show_links_data d = { .buf = buf };

	bus_for_each_dev(&mc.bus, NULL, &d, print_links);
	return d.offs;
}