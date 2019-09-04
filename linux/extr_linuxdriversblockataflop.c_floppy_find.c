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
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  disk; } ;

/* Variables and functions */
 int FD_MAX_UNITS ; 
 int NUM_DISK_MINORS ; 
 struct kobject* get_disk_and_module (int /*<<< orphan*/ ) ; 
 TYPE_1__* unit ; 

__attribute__((used)) static struct kobject *floppy_find(dev_t dev, int *part, void *data)
{
	int drive = *part & 3;
	int type  = *part >> 2;
	if (drive >= FD_MAX_UNITS || type > NUM_DISK_MINORS)
		return NULL;
	*part = 0;
	return get_disk_and_module(unit[drive].disk);
}