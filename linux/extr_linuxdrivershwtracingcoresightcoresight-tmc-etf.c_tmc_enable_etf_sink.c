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
struct tmc_drvdata {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
#define  CS_MODE_PERF 129 
#define  CS_MODE_SYSFS 128 
 int EINVAL ; 
 struct tmc_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int tmc_enable_etf_sink_perf (struct coresight_device*) ; 
 int tmc_enable_etf_sink_sysfs (struct coresight_device*) ; 

__attribute__((used)) static int tmc_enable_etf_sink(struct coresight_device *csdev, u32 mode)
{
	int ret;
	struct tmc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	switch (mode) {
	case CS_MODE_SYSFS:
		ret = tmc_enable_etf_sink_sysfs(csdev);
		break;
	case CS_MODE_PERF:
		ret = tmc_enable_etf_sink_perf(csdev);
		break;
	/* We shouldn't be here */
	default:
		ret = -EINVAL;
		break;
	}

	if (ret)
		return ret;

	dev_info(drvdata->dev, "TMC-ETB/ETF enabled\n");
	return 0;
}