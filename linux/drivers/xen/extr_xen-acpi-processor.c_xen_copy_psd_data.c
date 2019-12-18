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
struct xen_psd_package {int dummy; } ;
struct xen_processor_performance {int /*<<< orphan*/  domain_info; int /*<<< orphan*/  shared_type; } ;
struct acpi_psd_package {int num_processors; scalar_t__ coord_type; } ;
struct acpi_processor {TYPE_1__* performance; } ;
struct TYPE_2__ {struct acpi_psd_package domain_info; int /*<<< orphan*/  shared_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CPUFREQ_SHARED_TYPE_ALL ; 
 int /*<<< orphan*/  CPUFREQ_SHARED_TYPE_ANY ; 
 int /*<<< orphan*/  CPUFREQ_SHARED_TYPE_HW ; 
 scalar_t__ DOMAIN_COORD_TYPE_HW_ALL ; 
 scalar_t__ DOMAIN_COORD_TYPE_SW_ALL ; 
 scalar_t__ DOMAIN_COORD_TYPE_SW_ANY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct acpi_psd_package*,int) ; 

__attribute__((used)) static int xen_copy_psd_data(struct acpi_processor *_pr,
			     struct xen_processor_performance *dst)
{
	struct acpi_psd_package *pdomain;

	BUILD_BUG_ON(sizeof(struct xen_psd_package) !=
		     sizeof(struct acpi_psd_package));

	/* This information is enumerated only if acpi_processor_preregister_performance
	 * has been called.
	 */
	dst->shared_type = _pr->performance->shared_type;

	pdomain = &(_pr->performance->domain_info);

	/* 'acpi_processor_preregister_performance' does not parse if the
	 * num_processors <= 1, but Xen still requires it. Do it manually here.
	 */
	if (pdomain->num_processors <= 1) {
		if (pdomain->coord_type == DOMAIN_COORD_TYPE_SW_ALL)
			dst->shared_type = CPUFREQ_SHARED_TYPE_ALL;
		else if (pdomain->coord_type == DOMAIN_COORD_TYPE_HW_ALL)
			dst->shared_type = CPUFREQ_SHARED_TYPE_HW;
		else if (pdomain->coord_type == DOMAIN_COORD_TYPE_SW_ANY)
			dst->shared_type = CPUFREQ_SHARED_TYPE_ANY;

	}
	memcpy(&(dst->domain_info), pdomain, sizeof(struct acpi_psd_package));
	return 0;
}