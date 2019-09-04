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
typedef  enum port { ____Placeholder_port } port ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  PORT_A 133 
#define  PORT_B 132 
#define  PORT_C 131 
#define  PORT_D 130 
#define  PORT_E 129 
#define  PORT_F 128 
 int POWER_DOMAIN_PORT_DDI_A_LANES ; 
 int POWER_DOMAIN_PORT_DDI_B_LANES ; 
 int POWER_DOMAIN_PORT_DDI_C_LANES ; 
 int POWER_DOMAIN_PORT_DDI_D_LANES ; 
 int POWER_DOMAIN_PORT_DDI_E_LANES ; 
 int POWER_DOMAIN_PORT_DDI_F_LANES ; 
 int POWER_DOMAIN_PORT_OTHER ; 

enum intel_display_power_domain intel_port_to_power_domain(enum port port)
{
	switch (port) {
	case PORT_A:
		return POWER_DOMAIN_PORT_DDI_A_LANES;
	case PORT_B:
		return POWER_DOMAIN_PORT_DDI_B_LANES;
	case PORT_C:
		return POWER_DOMAIN_PORT_DDI_C_LANES;
	case PORT_D:
		return POWER_DOMAIN_PORT_DDI_D_LANES;
	case PORT_E:
		return POWER_DOMAIN_PORT_DDI_E_LANES;
	case PORT_F:
		return POWER_DOMAIN_PORT_DDI_F_LANES;
	default:
		MISSING_CASE(port);
		return POWER_DOMAIN_PORT_OTHER;
	}
}