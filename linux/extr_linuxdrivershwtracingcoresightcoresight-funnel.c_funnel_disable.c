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
struct funnel_drvdata {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct funnel_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  funnel_disable_hw (struct funnel_drvdata*,int) ; 

__attribute__((used)) static void funnel_disable(struct coresight_device *csdev, int inport,
			   int outport)
{
	struct funnel_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	funnel_disable_hw(drvdata, inport);

	dev_info(drvdata->dev, "FUNNEL inport %d disabled\n", inport);
}