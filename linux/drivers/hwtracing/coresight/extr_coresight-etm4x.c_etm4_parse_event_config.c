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
struct perf_event_attr {int config; scalar_t__ exclude_user; scalar_t__ exclude_kernel; } ;
struct perf_event {struct perf_event_attr attr; } ;
struct etmv4_config {int cfg; int /*<<< orphan*/  ccctlr; int /*<<< orphan*/  mode; } ;
struct etmv4_drvdata {scalar_t__ retstack; struct etmv4_config config; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ETM4_CFG_BIT_CTXTID ; 
 int /*<<< orphan*/  ETM_CYC_THRESHOLD_DEFAULT ; 
 int /*<<< orphan*/  ETM_MODE_EXCL_KERN ; 
 int /*<<< orphan*/  ETM_MODE_EXCL_USER ; 
 int ETM_OPT_CTXTID ; 
 int ETM_OPT_CYCACC ; 
 int ETM_OPT_RETSTK ; 
 int ETM_OPT_TS ; 
 int etm4_config_timestamp_event (struct etmv4_drvdata*) ; 
 int /*<<< orphan*/  etm4_set_default_config (struct etmv4_config*) ; 
 int etm4_set_event_filters (struct etmv4_drvdata*,struct perf_event*) ; 
 int /*<<< orphan*/  memset (struct etmv4_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int etm4_parse_event_config(struct etmv4_drvdata *drvdata,
				   struct perf_event *event)
{
	int ret = 0;
	struct etmv4_config *config = &drvdata->config;
	struct perf_event_attr *attr = &event->attr;

	if (!attr) {
		ret = -EINVAL;
		goto out;
	}

	/* Clear configuration from previous run */
	memset(config, 0, sizeof(struct etmv4_config));

	if (attr->exclude_kernel)
		config->mode = ETM_MODE_EXCL_KERN;

	if (attr->exclude_user)
		config->mode = ETM_MODE_EXCL_USER;

	/* Always start from the default config */
	etm4_set_default_config(config);

	/* Configure filters specified on the perf cmd line, if any. */
	ret = etm4_set_event_filters(drvdata, event);
	if (ret)
		goto out;

	/* Go from generic option to ETMv4 specifics */
	if (attr->config & BIT(ETM_OPT_CYCACC)) {
		config->cfg |= BIT(4);
		/* TRM: Must program this for cycacc to work */
		config->ccctlr = ETM_CYC_THRESHOLD_DEFAULT;
	}
	if (attr->config & BIT(ETM_OPT_TS)) {
		/*
		 * Configure timestamps to be emitted at regular intervals in
		 * order to correlate instructions executed on different CPUs
		 * (CPU-wide trace scenarios).
		 */
		ret = etm4_config_timestamp_event(drvdata);

		/*
		 * No need to go further if timestamp intervals can't
		 * be configured.
		 */
		if (ret)
			goto out;

		/* bit[11], Global timestamp tracing bit */
		config->cfg |= BIT(11);
	}

	if (attr->config & BIT(ETM_OPT_CTXTID))
		/* bit[6], Context ID tracing bit */
		config->cfg |= BIT(ETM4_CFG_BIT_CTXTID);

	/* return stack - enable if selected and supported */
	if ((attr->config & BIT(ETM_OPT_RETSTK)) && drvdata->retstack)
		/* bit[12], Return stack enable bit */
		config->cfg |= BIT(12);

out:
	return ret;
}