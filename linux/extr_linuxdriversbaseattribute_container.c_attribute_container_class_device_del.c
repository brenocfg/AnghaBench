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

/* Variables and functions */
 int /*<<< orphan*/  attribute_container_remove_attrs (struct device*) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 

void
attribute_container_class_device_del(struct device *classdev)
{
	attribute_container_remove_attrs(classdev);
	device_del(classdev);
}