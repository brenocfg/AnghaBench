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
 int ETHTOOL_FEC_AUTO ; 
 int ETHTOOL_FEC_BASER ; 
 int ETHTOOL_FEC_OFF ; 
 int ETHTOOL_FEC_RS ; 
 int MC_CMD_PHY_CAP_25G_BASER_FEC_LBN ; 
 int MC_CMD_PHY_CAP_25G_BASER_FEC_REQUESTED_LBN ; 
 int MC_CMD_PHY_CAP_BASER_FEC_LBN ; 
 int MC_CMD_PHY_CAP_BASER_FEC_REQUESTED_LBN ; 
 int MC_CMD_PHY_CAP_RS_FEC_LBN ; 
 int MC_CMD_PHY_CAP_RS_FEC_REQUESTED_LBN ; 

__attribute__((used)) static u32 mcdi_fec_caps_to_ethtool(u32 caps, bool is_25g)
{
	bool rs = caps & (1 << MC_CMD_PHY_CAP_RS_FEC_LBN),
	     rs_req = caps & (1 << MC_CMD_PHY_CAP_RS_FEC_REQUESTED_LBN),
	     baser = is_25g ? caps & (1 << MC_CMD_PHY_CAP_25G_BASER_FEC_LBN)
			    : caps & (1 << MC_CMD_PHY_CAP_BASER_FEC_LBN),
	     baser_req = is_25g ? caps & (1 << MC_CMD_PHY_CAP_25G_BASER_FEC_REQUESTED_LBN)
				: caps & (1 << MC_CMD_PHY_CAP_BASER_FEC_REQUESTED_LBN);

	if (!baser && !rs)
		return ETHTOOL_FEC_OFF;
	return (rs_req ? ETHTOOL_FEC_RS : 0) |
	       (baser_req ? ETHTOOL_FEC_BASER : 0) |
	       (baser == baser_req && rs == rs_req ? 0 : ETHTOOL_FEC_AUTO);
}