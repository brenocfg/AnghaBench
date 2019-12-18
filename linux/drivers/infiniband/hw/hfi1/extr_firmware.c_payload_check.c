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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,char const*,long,long) ; 

__attribute__((used)) static int payload_check(struct hfi1_devdata *dd, const char *name,
			 long file_size, long prefix_size)
{
	/* make sure we have some payload */
	if (prefix_size >= file_size) {
		dd_dev_err(dd,
			   "firmware \"%s\", size %ld, must be larger than %ld bytes\n",
			   name, file_size, prefix_size);
		return -EINVAL;
	}

	return 0;
}