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
struct ocxl_afu {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int MINOR (int /*<<< orphan*/ ) ; 
 struct ocxl_afu* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  minors_idr ; 
 int /*<<< orphan*/  ocxl_afu_get (struct ocxl_afu*) ; 

__attribute__((used)) static struct ocxl_afu *find_and_get_afu(dev_t devno)
{
	struct ocxl_afu *afu;
	int afu_minor;

	afu_minor = MINOR(devno);
	/*
	 * We don't declare an RCU critical section here, as our AFU
	 * is protected by a reference counter on the device. By the time the
	 * minor number of a device is removed from the idr, the ref count of
	 * the device is already at 0, so no user API will access that AFU and
	 * this function can't return it.
	 */
	afu = idr_find(&minors_idr, afu_minor);
	if (afu)
		ocxl_afu_get(afu);
	return afu;
}