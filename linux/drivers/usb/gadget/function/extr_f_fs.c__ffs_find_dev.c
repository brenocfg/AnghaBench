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
struct ffs_dev {int dummy; } ;

/* Variables and functions */
 struct ffs_dev* _ffs_do_find_dev (char const*) ; 
 struct ffs_dev* _ffs_get_single_dev () ; 

__attribute__((used)) static struct ffs_dev *_ffs_find_dev(const char *name)
{
	struct ffs_dev *dev;

	dev = _ffs_get_single_dev();
	if (dev)
		return dev;

	return _ffs_do_find_dev(name);
}