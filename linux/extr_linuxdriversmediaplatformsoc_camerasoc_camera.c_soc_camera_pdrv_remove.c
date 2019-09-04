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
struct soc_camera_device {int /*<<< orphan*/  list; } ;
struct platform_device {int id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_map ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct soc_camera_device* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_camera_pdrv_remove(struct platform_device *pdev)
{
	struct soc_camera_device *icd = platform_get_drvdata(pdev);
	int i;

	if (!icd)
		return -EINVAL;

	i = pdev->id;
	if (i < 0)
		i = 0;

	/*
	 * In synchronous mode with static platform devices this is called in a
	 * loop from drivers/base/dd.c::driver_detach(), no parallel execution,
	 * no need to lock. In asynchronous case the caller -
	 * soc_camera_host_unregister() - already holds the lock
	 */
	if (test_bit(i, device_map)) {
		clear_bit(i, device_map);
		list_del(&icd->list);
	}

	return 0;
}