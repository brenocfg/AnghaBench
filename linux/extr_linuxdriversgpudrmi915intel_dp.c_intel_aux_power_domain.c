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
struct intel_dp {int aux_ch; } ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
#define  AUX_CH_A 133 
#define  AUX_CH_B 132 
#define  AUX_CH_C 131 
#define  AUX_CH_D 130 
#define  AUX_CH_E 129 
#define  AUX_CH_F 128 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int POWER_DOMAIN_AUX_A ; 
 int POWER_DOMAIN_AUX_B ; 
 int POWER_DOMAIN_AUX_C ; 
 int POWER_DOMAIN_AUX_D ; 
 int POWER_DOMAIN_AUX_E ; 
 int POWER_DOMAIN_AUX_F ; 

__attribute__((used)) static enum intel_display_power_domain
intel_aux_power_domain(struct intel_dp *intel_dp)
{
	switch (intel_dp->aux_ch) {
	case AUX_CH_A:
		return POWER_DOMAIN_AUX_A;
	case AUX_CH_B:
		return POWER_DOMAIN_AUX_B;
	case AUX_CH_C:
		return POWER_DOMAIN_AUX_C;
	case AUX_CH_D:
		return POWER_DOMAIN_AUX_D;
	case AUX_CH_E:
		return POWER_DOMAIN_AUX_E;
	case AUX_CH_F:
		return POWER_DOMAIN_AUX_F;
	default:
		MISSING_CASE(intel_dp->aux_ch);
		return POWER_DOMAIN_AUX_A;
	}
}