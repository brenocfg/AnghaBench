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
struct enclosure_component {int slot; int number; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 struct enclosure_component* to_enclosure_component (struct device*) ; 

__attribute__((used)) static ssize_t get_component_slot(struct device *cdev,
				  struct device_attribute *attr, char *buf)
{
	struct enclosure_component *ecomp = to_enclosure_component(cdev);
	int slot;

	/* if the enclosure does not override then use 'number' as a stand-in */
	if (ecomp->slot >= 0)
		slot = ecomp->slot;
	else
		slot = ecomp->number;

	return snprintf(buf, 40, "%d\n", slot);
}