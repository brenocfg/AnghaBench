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

/* Variables and functions */
 unsigned int HV_PERF_DOMAIN_PHYS_CORE ; 
 unsigned int HV_PERF_DOMAIN_VCPU_HOME_CORE ; 
 unsigned int HV_PERF_DOMAIN_VCPU_REMOTE_NODE ; 
 scalar_t__ aggregate_result_elements ; 

__attribute__((used)) static bool domain_needs_aggregation(unsigned int domain)
{
	return aggregate_result_elements &&
			(domain == HV_PERF_DOMAIN_PHYS_CORE ||
			 (domain >= HV_PERF_DOMAIN_VCPU_HOME_CORE &&
			  domain <= HV_PERF_DOMAIN_VCPU_REMOTE_NODE));
}