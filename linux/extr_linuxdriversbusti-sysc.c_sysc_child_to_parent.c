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
struct sysc {int dummy; } ;
struct device {int /*<<< orphan*/ * type; struct device* parent; } ;

/* Variables and functions */
 struct sysc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sysc_device_type ; 

__attribute__((used)) static struct sysc *sysc_child_to_parent(struct device *dev)
{
	struct device *parent = dev->parent;

	if (!parent || parent->type != &sysc_device_type)
		return NULL;

	return dev_get_drvdata(parent);
}