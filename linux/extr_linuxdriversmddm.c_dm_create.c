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
struct mapped_device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 struct mapped_device* alloc_dev (int) ; 
 int dm_sysfs_init (struct mapped_device*) ; 
 int /*<<< orphan*/  free_dev (struct mapped_device*) ; 

int dm_create(int minor, struct mapped_device **result)
{
	int r;
	struct mapped_device *md;

	md = alloc_dev(minor);
	if (!md)
		return -ENXIO;

	r = dm_sysfs_init(md);
	if (r) {
		free_dev(md);
		return r;
	}

	*result = md;
	return 0;
}