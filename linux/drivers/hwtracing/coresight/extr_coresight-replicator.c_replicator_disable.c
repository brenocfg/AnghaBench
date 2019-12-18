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
struct replicator_drvdata {scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 struct replicator_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dynamic_replicator_disable (struct replicator_drvdata*,int,int) ; 

__attribute__((used)) static void replicator_disable(struct coresight_device *csdev, int inport,
			       int outport)
{
	struct replicator_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	if (drvdata->base)
		dynamic_replicator_disable(drvdata, inport, outport);
	dev_dbg(&csdev->dev, "REPLICATOR disabled\n");
}