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
struct coresight_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  coresight_release_platform_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coresight_remove_conns (struct coresight_device*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etm_perf_del_symlink_sink (struct coresight_device*) ; 

void coresight_unregister(struct coresight_device *csdev)
{
	etm_perf_del_symlink_sink(csdev);
	/* Remove references of that device in the topology */
	coresight_remove_conns(csdev);
	coresight_release_platform_data(csdev->pdata);
	device_unregister(&csdev->dev);
}