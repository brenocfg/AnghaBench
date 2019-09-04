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
struct module {int dummy; } ;
struct gendisk {TYPE_1__* fops; } ;
struct TYPE_2__ {struct module* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 

void put_disk_and_module(struct gendisk *disk)
{
	if (disk) {
		struct module *owner = disk->fops->owner;

		put_disk(disk);
		module_put(owner);
	}
}