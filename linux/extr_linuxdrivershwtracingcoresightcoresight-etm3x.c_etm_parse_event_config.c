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
struct etm_config {int ctrl; scalar_t__ mode; } ;
struct etm_drvdata {int etmccer; struct etm_config config; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETM3X_SUPPORTED_OPTIONS ; 
 int ETMCCER_RETSTACK ; 
 int ETMCR_RETURN_STACK ; 
 scalar_t__ ETM_MODE_EXCL_KERN ; 
 scalar_t__ ETM_MODE_EXCL_USER ; 
 int /*<<< orphan*/  etm_config_trace_mode (struct etm_config*) ; 
 int /*<<< orphan*/  etm_set_default (struct etm_config*) ; 
 int /*<<< orphan*/  memset (struct etm_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int etm_parse_event_config(struct etm_drvdata *drvdata,
				  struct perf_event *event)
{
	struct etm_config *config = &drvdata->config;
	struct perf_event_attr *attr = &event->attr;

	if (!attr)
		return -EINVAL;

	/* Clear configuration from previous run */
	memset(config, 0, sizeof(struct etm_config));

	if (attr->exclude_kernel)
		config->mode = ETM_MODE_EXCL_KERN;

	if (attr->exclude_user)
		config->mode = ETM_MODE_EXCL_USER;

	/* Always start from the default config */
	etm_set_default(config);

	/*
	 * By default the tracers are configured to trace the whole address
	 * range.  Narrow the field only if requested by user space.
	 */
	if (config->mode)
		etm_config_trace_mode(config);

	/*
	 * At this time only cycle accurate, return stack  and timestamp
	 * options are available.
	 */
	if (attr->config & ~ETM3X_SUPPORTED_OPTIONS)
		return -EINVAL;

	config->ctrl = attr->config;

	/*
	 * Possible to have cores with PTM (supports ret stack) and ETM
	 * (never has ret stack) on the same SoC. So if we have a request
	 * for return stack that can't be honoured on this core then
	 * clear the bit - trace will still continue normally
	 */
	if ((config->ctrl & ETMCR_RETURN_STACK) &&
	    !(drvdata->etmccer & ETMCCER_RETSTACK))
		config->ctrl &= ~ETMCR_RETURN_STACK;

	return 0;
}