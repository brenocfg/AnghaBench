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
struct intel_dp {scalar_t__ aux_ch; int aux_power_domain; } ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 scalar_t__ AUX_CH_A ; 
 int POWER_DOMAIN_AUX_IO_A ; 

__attribute__((used)) static inline enum intel_display_power_domain
intel_ddi_main_link_aux_domain(struct intel_dp *intel_dp)
{
	/* CNL HW requires corresponding AUX IOs to be powered up for PSR with
	 * DC states enabled at the same time, while for driver initiated AUX
	 * transfers we need the same AUX IOs to be powered but with DC states
	 * disabled. Accordingly use the AUX power domain here which leaves DC
	 * states enabled.
	 * However, for non-A AUX ports the corresponding non-EDP transcoders
	 * would have already enabled power well 2 and DC_OFF. This means we can
	 * acquire a wider POWER_DOMAIN_AUX_{B,C,D,F} reference instead of a
	 * specific AUX_IO reference without powering up any extra wells.
	 * Note that PSR is enabled only on Port A even though this function
	 * returns the correct domain for other ports too.
	 */
	return intel_dp->aux_ch == AUX_CH_A ? POWER_DOMAIN_AUX_IO_A :
					      intel_dp->aux_power_domain;
}