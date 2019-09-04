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
struct kobject {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int N_DRIVE ; 
 int /*<<< orphan*/ * disks ; 
 int /*<<< orphan*/  floppy_available (int) ; 
 int /*<<< orphan*/  floppy_type ; 
 struct kobject* get_disk_and_module (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kobject *floppy_find(dev_t dev, int *part, void *data)
{
	int drive = (*part & 3) | ((*part & 0x80) >> 5);
	if (drive >= N_DRIVE || !floppy_available(drive))
		return NULL;
	if (((*part >> 2) & 0x1f) >= ARRAY_SIZE(floppy_type))
		return NULL;
	*part = 0;
	return get_disk_and_module(disks[drive]);
}