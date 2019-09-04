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
struct TYPE_2__ {int hw_type; } ;
struct device {struct device* parent; } ;
typedef  struct parisc_device {TYPE_1__ id; struct device dev; } const parisc_device ;

/* Variables and functions */
 struct device const root ; 
 struct parisc_device const* to_parisc_device (struct device const*) ; 

const struct parisc_device *
find_pa_parent_type(const struct parisc_device *padev, int type)
{
	const struct device *dev = &padev->dev;
	while (dev != &root) {
		struct parisc_device *candidate = to_parisc_device(dev);
		if (candidate->id.hw_type == type)
			return candidate;
		dev = dev->parent;
	}

	return NULL;
}