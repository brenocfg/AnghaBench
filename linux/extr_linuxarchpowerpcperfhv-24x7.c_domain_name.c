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
#define  HV_PERF_DOMAIN_PHYS_CHIP 133 
#define  HV_PERF_DOMAIN_PHYS_CORE 132 
#define  HV_PERF_DOMAIN_VCPU_HOME_CHIP 131 
#define  HV_PERF_DOMAIN_VCPU_HOME_CORE 130 
#define  HV_PERF_DOMAIN_VCPU_HOME_NODE 129 
#define  HV_PERF_DOMAIN_VCPU_REMOTE_NODE 128 
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned int) ; 
 int /*<<< orphan*/  domain_is_valid (unsigned int) ; 

__attribute__((used)) static const char *domain_name(unsigned domain)
{
	if (!domain_is_valid(domain))
		return NULL;

	switch (domain) {
	case HV_PERF_DOMAIN_PHYS_CHIP:		return "Physical Chip";
	case HV_PERF_DOMAIN_PHYS_CORE:		return "Physical Core";
	case HV_PERF_DOMAIN_VCPU_HOME_CORE:	return "VCPU Home Core";
	case HV_PERF_DOMAIN_VCPU_HOME_CHIP:	return "VCPU Home Chip";
	case HV_PERF_DOMAIN_VCPU_HOME_NODE:	return "VCPU Home Node";
	case HV_PERF_DOMAIN_VCPU_REMOTE_NODE:	return "VCPU Remote Node";
	}

	WARN_ON_ONCE(domain);
	return NULL;
}