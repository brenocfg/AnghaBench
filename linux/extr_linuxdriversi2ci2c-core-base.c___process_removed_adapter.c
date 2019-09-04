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
struct device_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_do_del_adapter (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  to_i2c_driver (struct device_driver*) ; 

__attribute__((used)) static int __process_removed_adapter(struct device_driver *d, void *data)
{
	i2c_do_del_adapter(to_i2c_driver(d), data);
	return 0;
}