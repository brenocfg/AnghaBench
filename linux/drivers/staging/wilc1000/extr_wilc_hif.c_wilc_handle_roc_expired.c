#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct wilc_vif {TYPE_2__* ndev; struct host_if_drv* hif_drv; } ;
struct wilc_priv {scalar_t__ p2p_listen_state; } ;
struct wid {int size; int* val; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* expired ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct host_if_drv {TYPE_1__ remain_on_ch; } ;
struct TYPE_5__ {int /*<<< orphan*/  ieee80211_ptr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WID_REMAIN_ON_CHAN ; 
 int /*<<< orphan*/  WID_STR ; 
 int WILC_FALSE_FRMWR_CHANNEL ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wilc_priv* wdev_priv (int /*<<< orphan*/ ) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

__attribute__((used)) static int wilc_handle_roc_expired(struct wilc_vif *vif, u64 cookie)
{
	u8 remain_on_chan_flag;
	struct wid wid;
	int result;
	struct host_if_drv *hif_drv = vif->hif_drv;
	struct wilc_priv *priv = wdev_priv(vif->ndev->ieee80211_ptr);

	if (priv->p2p_listen_state) {
		remain_on_chan_flag = false;
		wid.id = WID_REMAIN_ON_CHAN;
		wid.type = WID_STR;
		wid.size = 2;

		wid.val = kmalloc(wid.size, GFP_KERNEL);
		if (!wid.val)
			return -ENOMEM;

		wid.val[0] = remain_on_chan_flag;
		wid.val[1] = WILC_FALSE_FRMWR_CHANNEL;

		result = wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
		kfree(wid.val);
		if (result != 0) {
			netdev_err(vif->ndev, "Failed to set remain channel\n");
			return -EINVAL;
		}

		if (hif_drv->remain_on_ch.expired) {
			hif_drv->remain_on_ch.expired(hif_drv->remain_on_ch.arg,
						      cookie);
		}
	} else {
		netdev_dbg(vif->ndev, "Not in listen state\n");
	}

	return 0;
}