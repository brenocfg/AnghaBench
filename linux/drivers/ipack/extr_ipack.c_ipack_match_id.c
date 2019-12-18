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
struct ipack_device_id {scalar_t__ device; scalar_t__ vendor; } ;
struct ipack_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ipack_match_one_device (struct ipack_device_id const*,struct ipack_device*) ; 

__attribute__((used)) static const struct ipack_device_id *
ipack_match_id(const struct ipack_device_id *ids, struct ipack_device *idev)
{
	if (ids) {
		while (ids->vendor || ids->device) {
			if (ipack_match_one_device(ids, idev))
				return ids;
			ids++;
		}
	}
	return NULL;
}