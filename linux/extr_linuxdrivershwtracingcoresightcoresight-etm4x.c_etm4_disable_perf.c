#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {struct etm_filters* addr_filters; } ;
struct perf_event {TYPE_1__ hw; } ;
struct etmv4_drvdata {scalar_t__ cpu; scalar_t__ base; } ;
struct etm_filters {int ssstatus; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 scalar_t__ TRCVICTLR ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etm4_disable_hw (struct etmv4_drvdata*) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ smp_processor_id () ; 

__attribute__((used)) static int etm4_disable_perf(struct coresight_device *csdev,
			     struct perf_event *event)
{
	u32 control;
	struct etm_filters *filters = event->hw.addr_filters;
	struct etmv4_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	if (WARN_ON_ONCE(drvdata->cpu != smp_processor_id()))
		return -EINVAL;

	etm4_disable_hw(drvdata);

	/*
	 * Check if the start/stop logic was active when the unit was stopped.
	 * That way we can re-enable the start/stop logic when the process is
	 * scheduled again.  Configuration of the start/stop logic happens in
	 * function etm4_set_event_filters().
	 */
	control = readl_relaxed(drvdata->base + TRCVICTLR);
	/* TRCVICTLR::SSSTATUS, bit[9] */
	filters->ssstatus = (control & BIT(9));

	return 0;
}