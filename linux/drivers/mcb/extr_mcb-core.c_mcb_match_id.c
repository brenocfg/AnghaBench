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
struct mcb_device_id {scalar_t__ device; } ;
struct mcb_device {scalar_t__ id; } ;

/* Variables and functions */

__attribute__((used)) static const struct mcb_device_id *mcb_match_id(const struct mcb_device_id *ids,
						struct mcb_device *dev)
{
	if (ids) {
		while (ids->device) {
			if (ids->device == dev->id)
				return ids;
			ids++;
		}
	}

	return NULL;
}