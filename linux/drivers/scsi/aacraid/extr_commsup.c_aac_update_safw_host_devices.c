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
struct aac_dev {int dummy; } ;

/* Variables and functions */
 int AAC_BUS_TARGET_LOOP ; 
 int /*<<< orphan*/  aac_add_safw_device (struct aac_dev*,int,int) ; 
 int aac_is_safw_device_exposed (struct aac_dev*,int,int) ; 
 scalar_t__ aac_is_safw_target_valid (struct aac_dev*,int,int) ; 
 int /*<<< orphan*/  aac_remove_safw_device (struct aac_dev*,int,int) ; 
 int aac_setup_safw_adapter (struct aac_dev*) ; 
 int get_bus_number (int) ; 
 int get_target_number (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aac_update_safw_host_devices(struct aac_dev *dev)
{
	int i;
	int bus;
	int target;
	int is_exposed = 0;
	int rcode = 0;

	rcode = aac_setup_safw_adapter(dev);
	if (unlikely(rcode < 0)) {
		goto out;
	}

	for (i = 0; i < AAC_BUS_TARGET_LOOP; i++) {

		bus = get_bus_number(i);
		target = get_target_number(i);

		is_exposed = aac_is_safw_device_exposed(dev, bus, target);

		if (aac_is_safw_target_valid(dev, bus, target) && !is_exposed)
			aac_add_safw_device(dev, bus, target);
		else if (!aac_is_safw_target_valid(dev, bus, target) &&
								is_exposed)
			aac_remove_safw_device(dev, bus, target);
	}
out:
	return rcode;
}