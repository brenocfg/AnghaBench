#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ice_vsi {TYPE_2__* back; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
struct ethtool_fecparam {int fec; } ;
typedef  enum ice_fec_mode { ____Placeholder_ice_fec_mode } ice_fec_mode ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_FEC_AUTO 132 
#define  ETHTOOL_FEC_BASER 131 
#define  ETHTOOL_FEC_NONE 130 
#define  ETHTOOL_FEC_OFF 129 
#define  ETHTOOL_FEC_RS 128 
 int ICE_FEC_AUTO ; 
 int ICE_FEC_BASER ; 
 int ICE_FEC_NONE ; 
 int ICE_FEC_RS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int ice_set_fec_cfg (struct net_device*,int) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
ice_set_fecparam(struct net_device *netdev, struct ethtool_fecparam *fecparam)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;
	enum ice_fec_mode fec;

	switch (fecparam->fec) {
	case ETHTOOL_FEC_AUTO:
		fec = ICE_FEC_AUTO;
		break;
	case ETHTOOL_FEC_RS:
		fec = ICE_FEC_RS;
		break;
	case ETHTOOL_FEC_BASER:
		fec = ICE_FEC_BASER;
		break;
	case ETHTOOL_FEC_OFF:
	case ETHTOOL_FEC_NONE:
		fec = ICE_FEC_NONE;
		break;
	default:
		dev_warn(&vsi->back->pdev->dev, "Unsupported FEC mode: %d\n",
			 fecparam->fec);
		return -EINVAL;
	}

	return ice_set_fec_cfg(netdev, fec);
}