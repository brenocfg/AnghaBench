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
typedef  int u32 ;
struct scmi_perf_info {struct perf_dom_info* dom_info; } ;
struct scmi_handle {struct scmi_perf_info* perf_priv; } ;
struct perf_dom_info {unsigned long mult_factor; } ;

/* Variables and functions */
 int scmi_perf_level_set (struct scmi_handle const*,int,unsigned long,int) ; 

__attribute__((used)) static int scmi_dvfs_freq_set(const struct scmi_handle *handle, u32 domain,
			      unsigned long freq, bool poll)
{
	struct scmi_perf_info *pi = handle->perf_priv;
	struct perf_dom_info *dom = pi->dom_info + domain;

	return scmi_perf_level_set(handle, domain, freq / dom->mult_factor,
				   poll);
}