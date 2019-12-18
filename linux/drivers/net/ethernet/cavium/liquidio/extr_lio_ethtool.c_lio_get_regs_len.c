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
struct octeon_device {int chip_id; } ;
struct net_device {int dummy; } ;
struct lio {struct octeon_device* oct_dev; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
#define  OCTEON_CN23XX_PF_VID 129 
#define  OCTEON_CN23XX_VF_VID 128 
 int OCT_ETHTOOL_REGDUMP_LEN ; 
 int OCT_ETHTOOL_REGDUMP_LEN_23XX ; 
 int OCT_ETHTOOL_REGDUMP_LEN_23XX_VF ; 

__attribute__((used)) static int lio_get_regs_len(struct net_device *dev)
{
	struct lio *lio = GET_LIO(dev);
	struct octeon_device *oct = lio->oct_dev;

	switch (oct->chip_id) {
	case OCTEON_CN23XX_PF_VID:
		return OCT_ETHTOOL_REGDUMP_LEN_23XX;
	case OCTEON_CN23XX_VF_VID:
		return OCT_ETHTOOL_REGDUMP_LEN_23XX_VF;
	default:
		return OCT_ETHTOOL_REGDUMP_LEN;
	}
}