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
struct device {int dummy; } ;
struct catu_drvdata {int /*<<< orphan*/  base; TYPE_1__* csdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ catu_wait_for_ready (struct catu_drvdata*) ; 
 int /*<<< orphan*/  catu_write_control (struct catu_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coresight_disclaim_device_unlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 

__attribute__((used)) static int catu_disable_hw(struct catu_drvdata *drvdata)
{
	int rc = 0;
	struct device *dev = &drvdata->csdev->dev;

	catu_write_control(drvdata, 0);
	coresight_disclaim_device_unlocked(drvdata->base);
	if (catu_wait_for_ready(drvdata)) {
		dev_info(dev, "Timeout while waiting for READY\n");
		rc = -EAGAIN;
	}

	dev_dbg(dev, "Disabled\n");
	return rc;
}