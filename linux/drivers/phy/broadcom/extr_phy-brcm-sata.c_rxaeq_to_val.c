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
typedef  enum brcm_sata_phy_rxaeq_mode { ____Placeholder_brcm_sata_phy_rxaeq_mode } brcm_sata_phy_rxaeq_mode ;

/* Variables and functions */
 int RXAEQ_MODE_AUTO ; 
 int RXAEQ_MODE_MANUAL ; 
 int RXAEQ_MODE_OFF ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static enum brcm_sata_phy_rxaeq_mode rxaeq_to_val(const char *m)
{
	if (!strcmp(m, "auto"))
		return RXAEQ_MODE_AUTO;
	else if (!strcmp(m, "manual"))
		return RXAEQ_MODE_MANUAL;
	else
		return RXAEQ_MODE_OFF;
}