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
struct fsg_lun {int removable; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int strtobool (char const*,int*) ; 

ssize_t fsg_store_removable(struct fsg_lun *curlun, const char *buf,
			    size_t count)
{
	bool		removable;
	int		ret;

	ret = strtobool(buf, &removable);
	if (ret)
		return ret;

	curlun->removable = removable;

	return count;
}