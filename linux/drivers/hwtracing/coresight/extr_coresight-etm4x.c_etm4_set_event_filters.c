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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {struct etm_filters* addr_filters; } ;
struct perf_event {TYPE_1__ hw; } ;
struct etmv4_config {int vissctlr; int viiectlr; int /*<<< orphan*/  vinst_ctrl; } ;
struct etmv4_drvdata {struct etmv4_config config; } ;
struct etm_filters {int nr_filters; int /*<<< orphan*/  ssstatus; struct etm_filter* etm_filter; } ;
struct etm_filter {int type; int /*<<< orphan*/  stop_addr; int /*<<< orphan*/  start_addr; } ;
typedef  enum etm_addr_type { ____Placeholder_etm_addr_type } etm_addr_type ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
#define  ETM_ADDR_TYPE_RANGE 130 
#define  ETM_ADDR_TYPE_START 129 
#define  ETM_ADDR_TYPE_STOP 128 
 int etm4_get_next_comparator (struct etmv4_drvdata*,int) ; 
 int /*<<< orphan*/  etm4_set_comparator_filter (struct etmv4_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  etm4_set_default_filter (struct etmv4_config*) ; 
 int /*<<< orphan*/  etm4_set_start_stop_filter (struct etmv4_config*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  perf_event_addr_filters_sync (struct perf_event*) ; 

__attribute__((used)) static int etm4_set_event_filters(struct etmv4_drvdata *drvdata,
				  struct perf_event *event)
{
	int i, comparator, ret = 0;
	u64 address;
	struct etmv4_config *config = &drvdata->config;
	struct etm_filters *filters = event->hw.addr_filters;

	if (!filters)
		goto default_filter;

	/* Sync events with what Perf got */
	perf_event_addr_filters_sync(event);

	/*
	 * If there are no filters to deal with simply go ahead with
	 * the default filter, i.e the entire address range.
	 */
	if (!filters->nr_filters)
		goto default_filter;

	for (i = 0; i < filters->nr_filters; i++) {
		struct etm_filter *filter = &filters->etm_filter[i];
		enum etm_addr_type type = filter->type;

		/* See if a comparator is free. */
		comparator = etm4_get_next_comparator(drvdata, type);
		if (comparator < 0) {
			ret = comparator;
			goto out;
		}

		switch (type) {
		case ETM_ADDR_TYPE_RANGE:
			etm4_set_comparator_filter(config,
						   filter->start_addr,
						   filter->stop_addr,
						   comparator);
			/*
			 * TRCVICTLR::SSSTATUS == 1, the start-stop logic is
			 * in the started state
			 */
			config->vinst_ctrl |= BIT(9);

			/* No start-stop filtering for ViewInst */
			config->vissctlr = 0x0;
			break;
		case ETM_ADDR_TYPE_START:
		case ETM_ADDR_TYPE_STOP:
			/* Get the right start or stop address */
			address = (type == ETM_ADDR_TYPE_START ?
				   filter->start_addr :
				   filter->stop_addr);

			/* Configure comparator */
			etm4_set_start_stop_filter(config, address,
						   comparator, type);

			/*
			 * If filters::ssstatus == 1, trace acquisition was
			 * started but the process was yanked away before the
			 * the stop address was hit.  As such the start/stop
			 * logic needs to be re-started so that tracing can
			 * resume where it left.
			 *
			 * The start/stop logic status when a process is
			 * scheduled out is checked in function
			 * etm4_disable_perf().
			 */
			if (filters->ssstatus)
				config->vinst_ctrl |= BIT(9);

			/* No include/exclude filtering for ViewInst */
			config->viiectlr = 0x0;
			break;
		default:
			ret = -EINVAL;
			goto out;
		}
	}

	goto out;


default_filter:
	etm4_set_default_filter(config);

out:
	return ret;
}