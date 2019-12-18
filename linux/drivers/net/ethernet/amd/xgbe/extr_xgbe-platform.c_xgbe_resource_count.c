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
struct platform_device {int num_resources; struct resource* resource; } ;

/* Variables and functions */
 unsigned int resource_type (struct resource*) ; 

__attribute__((used)) static unsigned int xgbe_resource_count(struct platform_device *pdev,
					unsigned int type)
{
	unsigned int count;
	int i;

	for (i = 0, count = 0; i < pdev->num_resources; i++) {
		struct resource *res = &pdev->resource[i];

		if (type == resource_type(res))
			count++;
	}

	return count;
}