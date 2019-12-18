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
typedef  enum sas_linkrate { ____Placeholder_sas_linkrate } sas_linkrate ;

/* Variables and functions */
 int SAS_LINK_RATE_6_0_GBPS ; 

__attribute__((used)) static enum sas_linkrate phy_get_max_linkrate_v1_hw(void)
{
	return SAS_LINK_RATE_6_0_GBPS;
}