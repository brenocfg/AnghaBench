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
struct pcie_link_state {int clkpm_default; } ;

/* Variables and functions */
#define  POLICY_DEFAULT 131 
#define  POLICY_PERFORMANCE 130 
#define  POLICY_POWERSAVE 129 
#define  POLICY_POWER_SUPERSAVE 128 
 int aspm_policy ; 

__attribute__((used)) static int policy_to_clkpm_state(struct pcie_link_state *link)
{
	switch (aspm_policy) {
	case POLICY_PERFORMANCE:
		/* Disable ASPM and Clock PM */
		return 0;
	case POLICY_POWERSAVE:
	case POLICY_POWER_SUPERSAVE:
		/* Enable Clock PM */
		return 1;
	case POLICY_DEFAULT:
		return link->clkpm_default;
	}
	return 0;
}