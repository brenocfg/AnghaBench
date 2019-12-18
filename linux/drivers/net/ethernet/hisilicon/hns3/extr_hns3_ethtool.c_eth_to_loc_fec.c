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
typedef  unsigned int u32 ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 unsigned int ETHTOOL_FEC_AUTO ; 
 unsigned int ETHTOOL_FEC_BASER ; 
 unsigned int ETHTOOL_FEC_OFF ; 
 unsigned int ETHTOOL_FEC_RS ; 
 int /*<<< orphan*/  HNAE3_FEC_AUTO ; 
 int /*<<< orphan*/  HNAE3_FEC_BASER ; 
 int /*<<< orphan*/  HNAE3_FEC_RS ; 

__attribute__((used)) static unsigned int eth_to_loc_fec(unsigned int eth_fec)
{
	u32 loc_fec = 0;

	if (eth_fec & ETHTOOL_FEC_OFF)
		return loc_fec;

	if (eth_fec & ETHTOOL_FEC_AUTO)
		loc_fec |= BIT(HNAE3_FEC_AUTO);
	if (eth_fec & ETHTOOL_FEC_RS)
		loc_fec |= BIT(HNAE3_FEC_RS);
	if (eth_fec & ETHTOOL_FEC_BASER)
		loc_fec |= BIT(HNAE3_FEC_BASER);

	return loc_fec;
}