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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmu_info_proc_mutex ; 
 int pmu_ioctl (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long pmu_unlocked_ioctl(struct file *filp,
			       u_int cmd, u_long arg)
{
	int ret;

	mutex_lock(&pmu_info_proc_mutex);
	ret = pmu_ioctl(filp, cmd, arg);
	mutex_unlock(&pmu_info_proc_mutex);

	return ret;
}