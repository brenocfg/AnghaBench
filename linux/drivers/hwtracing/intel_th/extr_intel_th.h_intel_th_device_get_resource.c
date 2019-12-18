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
struct resource {int dummy; } ;
struct intel_th_device {int num_resources; struct resource* resource; } ;

/* Variables and functions */
 unsigned int resource_type (struct resource*) ; 

__attribute__((used)) static inline struct resource *
intel_th_device_get_resource(struct intel_th_device *thdev, unsigned int type,
			     unsigned int num)
{
	int i;

	for (i = 0; i < thdev->num_resources; i++)
		if (resource_type(&thdev->resource[i]) == type && !num--)
			return &thdev->resource[i];

	return NULL;
}