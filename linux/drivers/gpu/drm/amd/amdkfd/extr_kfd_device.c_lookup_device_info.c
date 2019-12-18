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
struct kfd_device_info {int dummy; } ;
struct TYPE_3__ {unsigned short did; struct kfd_device_info const* device_info; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned short) ; 
 int /*<<< orphan*/  kfd_device ; 
 TYPE_1__* supported_devices ; 

__attribute__((used)) static const struct kfd_device_info *lookup_device_info(unsigned short did)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(supported_devices); i++) {
		if (supported_devices[i].did == did) {
			WARN_ON(!supported_devices[i].device_info);
			return supported_devices[i].device_info;
		}
	}

	dev_warn(kfd_device, "DID %04x is missing in supported_devices\n",
		 did);

	return NULL;
}