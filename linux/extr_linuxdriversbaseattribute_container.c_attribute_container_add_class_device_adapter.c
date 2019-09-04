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
struct attribute_container {int dummy; } ;

/* Variables and functions */
 int attribute_container_add_class_device (struct device*) ; 

int
attribute_container_add_class_device_adapter(struct attribute_container *cont,
					     struct device *dev,
					     struct device *classdev)
{
	return attribute_container_add_class_device(classdev);
}