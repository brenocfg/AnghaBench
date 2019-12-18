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
typedef  int u8 ;
typedef  unsigned int u32 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 unsigned int ETHTOOL_FEC_AUTO ; 
 unsigned int ETHTOOL_FEC_BASER ; 
 unsigned int ETHTOOL_FEC_OFF ; 
 unsigned int ETHTOOL_FEC_RS ; 
 int /*<<< orphan*/  HNAE3_FEC_AUTO ; 
 int /*<<< orphan*/  HNAE3_FEC_BASER ; 
 int /*<<< orphan*/  HNAE3_FEC_RS ; 

__attribute__((used)) static unsigned int loc_to_eth_fec(u8 loc_fec)
{
	u32 eth_fec = 0;

	if (loc_fec & BIT(HNAE3_FEC_AUTO))
		eth_fec |= ETHTOOL_FEC_AUTO;
	if (loc_fec & BIT(HNAE3_FEC_RS))
		eth_fec |= ETHTOOL_FEC_RS;
	if (loc_fec & BIT(HNAE3_FEC_BASER))
		eth_fec |= ETHTOOL_FEC_BASER;

	/* if nothing is set, then FEC is off */
	if (!eth_fec)
		eth_fec = ETHTOOL_FEC_OFF;

	return eth_fec;
}