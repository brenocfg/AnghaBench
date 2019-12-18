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
struct device {int dummy; } ;
struct enclosure_component {int number; struct device cdev; } ;

/* Variables and functions */
 int device_register (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

int enclosure_component_register(struct enclosure_component *ecomp)
{
	struct device *cdev;
	int err;

	cdev = &ecomp->cdev;
	err = device_register(cdev);
	if (err) {
		ecomp->number = -1;
		put_device(cdev);
		return err;
	}

	return 0;
}