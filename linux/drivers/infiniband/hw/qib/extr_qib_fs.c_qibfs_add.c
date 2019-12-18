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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int add_cntr_files (int /*<<< orphan*/ *,struct qib_devdata*) ; 
 int /*<<< orphan*/ * qib_super ; 

int qibfs_add(struct qib_devdata *dd)
{
	int ret;

	/*
	 * On first unit initialized, qib_super will not yet exist
	 * because nobody has yet tried to mount the filesystem, so
	 * we can't consider that to be an error; if an error occurs
	 * during the mount, that will get a complaint, so this is OK.
	 * add_cntr_files() for all units is done at mount from
	 * qibfs_fill_super(), so one way or another, everything works.
	 */
	if (qib_super == NULL)
		ret = 0;
	else
		ret = add_cntr_files(qib_super, dd);
	return ret;
}