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
struct catu_drvdata {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ catu_wait_for_ready (struct catu_drvdata*) ; 
 int /*<<< orphan*/  catu_write_control (struct catu_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int catu_disable_hw(struct catu_drvdata *drvdata)
{
	int rc = 0;

	catu_write_control(drvdata, 0);
	if (catu_wait_for_ready(drvdata)) {
		dev_info(drvdata->dev, "Timeout while waiting for READY\n");
		rc = -EAGAIN;
	}

	dev_dbg(drvdata->dev, "Disabled\n");
	return rc;
}