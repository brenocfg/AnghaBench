#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ umode_t ;
struct kobject {int dummy; } ;
struct attribute {scalar_t__ mode; } ;
struct TYPE_4__ {struct attribute attr; } ;
struct TYPE_3__ {struct attribute attr; } ;

/* Variables and functions */
 TYPE_2__ dev_attr_aux3 ; 
 TYPE_1__ dev_attr_gpio3 ; 
 scalar_t__ gpio3 ; 

__attribute__((used)) static umode_t ad7877_attr_is_visible(struct kobject *kobj,
				     struct attribute *attr, int n)
{
	umode_t mode = attr->mode;

	if (attr == &dev_attr_aux3.attr) {
		if (gpio3)
			mode = 0;
	} else if (attr == &dev_attr_gpio3.attr) {
		if (!gpio3)
			mode = 0;
	}

	return mode;
}