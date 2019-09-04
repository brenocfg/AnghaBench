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
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_25000baseCR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT ; 
 unsigned int FW_PORT_CAP32_SPEED_100G ; 
 unsigned int FW_PORT_CAP32_SPEED_100M ; 
 unsigned int FW_PORT_CAP32_SPEED_10G ; 
 unsigned int FW_PORT_CAP32_SPEED_1G ; 
 unsigned int FW_PORT_CAP32_SPEED_25G ; 
 unsigned int FW_PORT_CAP32_SPEED_40G ; 
 unsigned int FW_PORT_CAP32_SPEED_50G ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long const*) ; 

__attribute__((used)) static unsigned int lmm_to_fw_caps(const unsigned long *link_mode_mask)
{
	unsigned int fw_caps = 0;

	#define LMM_TO_FW_CAPS(__lmm_name, __fw_name) \
		do { \
			if (test_bit(ETHTOOL_LINK_MODE_ ## __lmm_name ## _BIT, \
				     link_mode_mask)) \
				fw_caps |= FW_PORT_CAP32_ ## __fw_name; \
		} while (0)

	LMM_TO_FW_CAPS(100baseT_Full, SPEED_100M);
	LMM_TO_FW_CAPS(1000baseT_Full, SPEED_1G);
	LMM_TO_FW_CAPS(10000baseT_Full, SPEED_10G);
	LMM_TO_FW_CAPS(40000baseSR4_Full, SPEED_40G);
	LMM_TO_FW_CAPS(25000baseCR_Full, SPEED_25G);
	LMM_TO_FW_CAPS(50000baseCR2_Full, SPEED_50G);
	LMM_TO_FW_CAPS(100000baseCR4_Full, SPEED_100G);

	#undef LMM_TO_FW_CAPS

	return fw_caps;
}