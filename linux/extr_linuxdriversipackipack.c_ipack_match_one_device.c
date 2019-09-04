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
struct ipack_device_id {scalar_t__ format; scalar_t__ vendor; scalar_t__ device; } ;
struct ipack_device {scalar_t__ id_format; scalar_t__ id_vendor; scalar_t__ id_device; } ;

/* Variables and functions */
 scalar_t__ IPACK_ANY_FORMAT ; 
 scalar_t__ IPACK_ANY_ID ; 

__attribute__((used)) static inline const struct ipack_device_id *
ipack_match_one_device(const struct ipack_device_id *id,
		       const struct ipack_device *device)
{
	if ((id->format == IPACK_ANY_FORMAT ||
				id->format == device->id_format) &&
	    (id->vendor == IPACK_ANY_ID || id->vendor == device->id_vendor) &&
	    (id->device == IPACK_ANY_ID || id->device == device->id_device))
		return id;
	return NULL;
}