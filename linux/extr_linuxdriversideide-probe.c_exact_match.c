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
struct kobject {int dummy; } ;
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {struct kobject kobj; } ;

/* Variables and functions */
 int PARTN_BITS ; 
 TYPE_1__* disk_to_dev (struct gendisk*) ; 

__attribute__((used)) static struct kobject *exact_match(dev_t dev, int *part, void *data)
{
	struct gendisk *p = data;
	*part &= (1 << PARTN_BITS) - 1;
	return &disk_to_dev(p)->kobj;
}