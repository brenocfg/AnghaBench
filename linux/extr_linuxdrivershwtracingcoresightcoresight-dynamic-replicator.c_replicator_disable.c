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
struct replicator_state {int /*<<< orphan*/  dev; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ REPLICATOR_IDFILTER0 ; 
 scalar_t__ REPLICATOR_IDFILTER1 ; 
 struct replicator_state* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void replicator_disable(struct coresight_device *csdev, int inport,
				int outport)
{
	struct replicator_state *drvdata = dev_get_drvdata(csdev->dev.parent);

	CS_UNLOCK(drvdata->base);

	/* disable the flow of ATB data through port */
	if (outport == 0)
		writel_relaxed(0xff, drvdata->base + REPLICATOR_IDFILTER0);
	else
		writel_relaxed(0xff, drvdata->base + REPLICATOR_IDFILTER1);

	CS_LOCK(drvdata->base);

	dev_info(drvdata->dev, "REPLICATOR disabled\n");
}