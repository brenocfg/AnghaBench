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
struct funnel_drvdata {scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int) ; 
 struct funnel_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int dynamic_funnel_enable_hw (struct funnel_drvdata*,int) ; 

__attribute__((used)) static int funnel_enable(struct coresight_device *csdev, int inport,
			 int outport)
{
	int rc = 0;
	struct funnel_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	if (drvdata->base)
		rc = dynamic_funnel_enable_hw(drvdata, inport);

	if (!rc)
		dev_dbg(&csdev->dev, "FUNNEL inport %d enabled\n", inport);
	return rc;
}