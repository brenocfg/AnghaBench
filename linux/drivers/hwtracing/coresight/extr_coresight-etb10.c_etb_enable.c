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
typedef  int u32 ;
struct coresight_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CS_MODE_PERF 129 
#define  CS_MODE_SYSFS 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int etb_enable_perf (struct coresight_device*,void*) ; 
 int etb_enable_sysfs (struct coresight_device*) ; 

__attribute__((used)) static int etb_enable(struct coresight_device *csdev, u32 mode, void *data)
{
	int ret;

	switch (mode) {
	case CS_MODE_SYSFS:
		ret = etb_enable_sysfs(csdev);
		break;
	case CS_MODE_PERF:
		ret = etb_enable_perf(csdev, data);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (ret)
		return ret;

	dev_dbg(&csdev->dev, "ETB enabled\n");
	return 0;
}