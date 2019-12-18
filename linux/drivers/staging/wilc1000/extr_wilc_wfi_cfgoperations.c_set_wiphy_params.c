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
struct wiphy {int retry_short; int retry_long; int frag_threshold; int rts_threshold; } ;
struct wilc_priv {int /*<<< orphan*/  dev; } ;
struct wilc_vif {int /*<<< orphan*/  ndev; struct wilc_priv priv; } ;
struct wilc {int dummy; } ;
struct cfg_param_attr {int short_retry_limit; int long_retry_limit; int frag_threshold; int rts_threshold; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WILC_CFG_PARAM_FRAG_THRESHOLD ; 
 int /*<<< orphan*/  WILC_CFG_PARAM_RETRY_LONG ; 
 int /*<<< orphan*/  WILC_CFG_PARAM_RETRY_SHORT ; 
 int /*<<< orphan*/  WILC_CFG_PARAM_RTS_THRESHOLD ; 
 int WIPHY_PARAM_FRAG_THRESHOLD ; 
 int WIPHY_PARAM_RETRY_LONG ; 
 int WIPHY_PARAM_RETRY_SHORT ; 
 int WIPHY_PARAM_RTS_THRESHOLD ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct wilc_vif* wilc_get_interface (struct wilc*) ; 
 int wilc_hif_set_cfg (struct wilc_vif*,struct cfg_param_attr*) ; 
 struct wilc* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int set_wiphy_params(struct wiphy *wiphy, u32 changed)
{
	int ret;
	struct cfg_param_attr cfg_param_val;
	struct wilc *wl = wiphy_priv(wiphy);
	struct wilc_vif *vif;
	struct wilc_priv *priv;

	vif = wilc_get_interface(wl);
	if (!vif)
		return -EINVAL;

	priv = &vif->priv;
	cfg_param_val.flag = 0;

	if (changed & WIPHY_PARAM_RETRY_SHORT) {
		netdev_dbg(vif->ndev,
			   "Setting WIPHY_PARAM_RETRY_SHORT %d\n",
			   wiphy->retry_short);
		cfg_param_val.flag  |= WILC_CFG_PARAM_RETRY_SHORT;
		cfg_param_val.short_retry_limit = wiphy->retry_short;
	}
	if (changed & WIPHY_PARAM_RETRY_LONG) {
		netdev_dbg(vif->ndev,
			   "Setting WIPHY_PARAM_RETRY_LONG %d\n",
			   wiphy->retry_long);
		cfg_param_val.flag |= WILC_CFG_PARAM_RETRY_LONG;
		cfg_param_val.long_retry_limit = wiphy->retry_long;
	}
	if (changed & WIPHY_PARAM_FRAG_THRESHOLD) {
		if (wiphy->frag_threshold > 255 &&
		    wiphy->frag_threshold < 7937) {
			netdev_dbg(vif->ndev,
				   "Setting WIPHY_PARAM_FRAG_THRESHOLD %d\n",
				   wiphy->frag_threshold);
			cfg_param_val.flag |= WILC_CFG_PARAM_FRAG_THRESHOLD;
			cfg_param_val.frag_threshold = wiphy->frag_threshold;
		} else {
			netdev_err(vif->ndev,
				   "Fragmentation threshold out of range\n");
			return -EINVAL;
		}
	}

	if (changed & WIPHY_PARAM_RTS_THRESHOLD) {
		if (wiphy->rts_threshold > 255) {
			netdev_dbg(vif->ndev,
				   "Setting WIPHY_PARAM_RTS_THRESHOLD %d\n",
				   wiphy->rts_threshold);
			cfg_param_val.flag |= WILC_CFG_PARAM_RTS_THRESHOLD;
			cfg_param_val.rts_threshold = wiphy->rts_threshold;
		} else {
			netdev_err(vif->ndev, "RTS threshold out of range\n");
			return -EINVAL;
		}
	}

	ret = wilc_hif_set_cfg(vif, &cfg_param_val);
	if (ret)
		netdev_err(priv->dev, "Error in setting WIPHY PARAMS\n");

	return ret;
}