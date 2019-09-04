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
struct device {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_adapter_type ; 
 int i2c_do_add_adapter (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_i2c_adapter (struct device*) ; 

__attribute__((used)) static int __process_new_driver(struct device *dev, void *data)
{
	if (dev->type != &i2c_adapter_type)
		return 0;
	return i2c_do_add_adapter(data, to_i2c_adapter(dev));
}