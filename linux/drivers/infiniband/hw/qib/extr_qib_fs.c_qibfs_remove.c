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
 scalar_t__ qib_super ; 
 int remove_device_files (scalar_t__,struct qib_devdata*) ; 

int qibfs_remove(struct qib_devdata *dd)
{
	int ret = 0;

	if (qib_super)
		ret = remove_device_files(qib_super, dd);

	return ret;
}