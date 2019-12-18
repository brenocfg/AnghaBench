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
struct ocxl_file_info {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 struct ocxl_file_info* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minors_idr ; 

__attribute__((used)) static struct ocxl_file_info *find_file_info(dev_t devno)
{
	struct ocxl_file_info *info;

	/*
	 * We don't declare an RCU critical section here, as our AFU
	 * is protected by a reference counter on the device. By the time the
	 * info reference is removed from the idr, the ref count of
	 * the device is already at 0, so no user API will access that AFU and
	 * this function can't return it.
	 */
	info = idr_find(&minors_idr, MINOR(devno));
	return info;
}