#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct perf_event {int dummy; } ;
struct etmv4_drvdata {int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_MODE_DISABLED ; 
#define  CS_MODE_PERF 129 
#define  CS_MODE_SYSFS 128 
 int EBUSY ; 
 int EINVAL ; 
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int etm4_enable_perf (struct coresight_device*,struct perf_event*) ; 
 int etm4_enable_sysfs (struct coresight_device*) ; 
 int local_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  local_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int etm4_enable(struct coresight_device *csdev,
		       struct perf_event *event, u32 mode)
{
	int ret;
	u32 val;
	struct etmv4_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	val = local_cmpxchg(&drvdata->mode, CS_MODE_DISABLED, mode);

	/* Someone is already using the tracer */
	if (val)
		return -EBUSY;

	switch (mode) {
	case CS_MODE_SYSFS:
		ret = etm4_enable_sysfs(csdev);
		break;
	case CS_MODE_PERF:
		ret = etm4_enable_perf(csdev, event);
		break;
	default:
		ret = -EINVAL;
	}

	/* The tracer didn't start */
	if (ret)
		local_set(&drvdata->mode, CS_MODE_DISABLED);

	return ret;
}