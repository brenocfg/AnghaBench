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

/* Variables and functions */
 int ADVERTISE_FIBER_1000FULL ; 
 int ADVERTISE_FIBER_1000HALF ; 
 int ADVERTISE_PAUSE_ASYM_FIBER ; 
 int ADVERTISE_PAUSE_FIBER ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Asym_Pause_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Pause_BIT ; 
 int LPA_PAUSE_ASYM_FIBER ; 
 scalar_t__ linkmode_test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static inline u32 linkmode_adv_to_fiber_adv_t(unsigned long *advertise)
{
	u32 result = 0;

	if (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT, advertise))
		result |= ADVERTISE_FIBER_1000HALF;
	if (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT, advertise))
		result |= ADVERTISE_FIBER_1000FULL;

	if (linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, advertise) &&
	    linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT, advertise))
		result |= LPA_PAUSE_ASYM_FIBER;
	else if (linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT, advertise))
		result |= (ADVERTISE_PAUSE_FIBER
			   & (~ADVERTISE_PAUSE_ASYM_FIBER));

	return result;
}