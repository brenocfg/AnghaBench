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
struct enclosure_device {TYPE_1__* cb; } ;
struct enclosure_component {size_t status; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_status ) (struct enclosure_device*,struct enclosure_component*) ;} ;

/* Variables and functions */
 char** enclosure_status ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct enclosure_device*,struct enclosure_component*) ; 
 struct enclosure_component* to_enclosure_component (struct device*) ; 
 struct enclosure_device* to_enclosure_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t get_component_status(struct device *cdev,
				    struct device_attribute *attr,char *buf)
{
	struct enclosure_device *edev = to_enclosure_device(cdev->parent);
	struct enclosure_component *ecomp = to_enclosure_component(cdev);

	if (edev->cb->get_status)
		edev->cb->get_status(edev, ecomp);
	return snprintf(buf, 40, "%s\n", enclosure_status[ecomp->status]);
}