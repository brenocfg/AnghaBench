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
struct velocity_info {int no_eeprom; TYPE_1__* dev; int /*<<< orphan*/  memaddr; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VELOCITY_IO_SIZE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int of_address_to_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 scalar_t__ of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ resource_size (struct resource*) ; 

__attribute__((used)) static int velocity_get_platform_info(struct velocity_info *vptr)
{
	struct resource res;
	int ret;

	if (of_get_property(vptr->dev->of_node, "no-eeprom", NULL))
		vptr->no_eeprom = 1;

	ret = of_address_to_resource(vptr->dev->of_node, 0, &res);
	if (ret) {
		dev_err(vptr->dev, "unable to find memory address\n");
		return ret;
	}

	vptr->memaddr = res.start;

	if (resource_size(&res) < VELOCITY_IO_SIZE) {
		dev_err(vptr->dev, "memory region is too small.\n");
		return -EINVAL;
	}

	return 0;
}