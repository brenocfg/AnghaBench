#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct scmi_perf_ops {int (* freq_set ) (TYPE_3__*,int /*<<< orphan*/ ,int,int) ;} ;
struct scmi_data {int /*<<< orphan*/  domain_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_freq; } ;
struct cpufreq_policy {TYPE_1__ cpuinfo; int /*<<< orphan*/  related_cpus; TYPE_2__* freq_table; struct scmi_data* driver_data; } ;
struct TYPE_7__ {struct scmi_perf_ops* perf_ops; } ;
struct TYPE_6__ {int frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_set_freq_scale (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* handle ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
scmi_cpufreq_set_target(struct cpufreq_policy *policy, unsigned int index)
{
	int ret;
	struct scmi_data *priv = policy->driver_data;
	struct scmi_perf_ops *perf_ops = handle->perf_ops;
	u64 freq = policy->freq_table[index].frequency;

	ret = perf_ops->freq_set(handle, priv->domain_id, freq * 1000, false);
	if (!ret)
		arch_set_freq_scale(policy->related_cpus, freq,
				    policy->cpuinfo.max_freq);
	return ret;
}