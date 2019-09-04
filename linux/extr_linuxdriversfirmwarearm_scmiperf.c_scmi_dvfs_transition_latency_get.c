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
struct scmi_perf_info {struct perf_dom_info* dom_info; } ;
struct scmi_handle {struct scmi_perf_info* perf_priv; } ;
struct perf_dom_info {int opp_count; TYPE_1__* opp; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int trans_latency_us; } ;

/* Variables and functions */
 int scmi_dev_domain_id (struct device*) ; 

__attribute__((used)) static int scmi_dvfs_transition_latency_get(const struct scmi_handle *handle,
					    struct device *dev)
{
	struct perf_dom_info *dom;
	struct scmi_perf_info *pi = handle->perf_priv;
	int domain = scmi_dev_domain_id(dev);

	if (domain < 0)
		return domain;

	dom = pi->dom_info + domain;
	/* uS to nS */
	return dom->opp[dom->opp_count - 1].trans_latency_us * 1000;
}