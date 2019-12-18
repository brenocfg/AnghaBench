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
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Asym_Pause_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Pause_BIT ; 
 int /*<<< orphan*/  linkmode_mod_bit (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void phy_copy_pause_bits(unsigned long *dst, unsigned long *src)
{
	linkmode_mod_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, dst,
		linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, src));
	linkmode_mod_bit(ETHTOOL_LINK_MODE_Pause_BIT, dst,
		linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT, src));
}