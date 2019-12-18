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
typedef  scalar_t__ u32 ;
struct replicator_drvdata {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ REPLICATOR_IDFILTER0 ; 
 scalar_t__ REPLICATOR_IDFILTER1 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  coresight_disclaim_device_unlocked (scalar_t__) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void dynamic_replicator_disable(struct replicator_drvdata *drvdata,
				       int inport, int outport)
{
	u32 reg;

	switch (outport) {
	case 0:
		reg = REPLICATOR_IDFILTER0;
		break;
	case 1:
		reg = REPLICATOR_IDFILTER1;
		break;
	default:
		WARN_ON(1);
		return;
	}

	CS_UNLOCK(drvdata->base);

	/* disable the flow of ATB data through port */
	writel_relaxed(0xff, drvdata->base + reg);

	if ((readl_relaxed(drvdata->base + REPLICATOR_IDFILTER0) == 0xff) &&
	    (readl_relaxed(drvdata->base + REPLICATOR_IDFILTER1) == 0xff))
		coresight_disclaim_device_unlocked(drvdata->base);
	CS_LOCK(drvdata->base);
}