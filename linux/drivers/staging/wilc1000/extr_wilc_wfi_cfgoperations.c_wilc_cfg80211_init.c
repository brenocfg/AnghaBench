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
struct wilc_vif {int dummy; } ;
struct wilc_hif_func {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
struct wilc {int io_type; int /*<<< orphan*/  wiphy; int /*<<< orphan*/  hif_workqueue; TYPE_2__ rxq_head; TYPE_1__ txq_head; int /*<<< orphan*/  chip_ps_state; struct wilc_hif_func const* hif_func; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct wilc_vif*) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int PTR_ERR (struct wilc_vif*) ; 
 int /*<<< orphan*/  WILC_CHIP_WAKEDUP ; 
 int /*<<< orphan*/  WILC_STATION_MODE ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct wilc* wilc_create_wiphy (struct device*) ; 
 struct wilc_vif* wilc_netdev_ifc_init (struct wilc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wilc_wlan_cfg_deinit (struct wilc*) ; 
 int wilc_wlan_cfg_init (struct wilc*) ; 
 int /*<<< orphan*/  wiphy_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_init_locks (struct wilc*) ; 

int wilc_cfg80211_init(struct wilc **wilc, struct device *dev, int io_type,
		       const struct wilc_hif_func *ops)
{
	struct wilc *wl;
	struct wilc_vif *vif;
	int ret;

	wl = wilc_create_wiphy(dev);
	if (!wl)
		return -EINVAL;

	ret = wilc_wlan_cfg_init(wl);
	if (ret)
		goto free_wl;

	*wilc = wl;
	wl->io_type = io_type;
	wl->hif_func = ops;
	wl->chip_ps_state = WILC_CHIP_WAKEDUP;
	INIT_LIST_HEAD(&wl->txq_head.list);
	INIT_LIST_HEAD(&wl->rxq_head.list);

	wl->hif_workqueue = create_singlethread_workqueue("WILC_wq");
	if (!wl->hif_workqueue) {
		ret = -ENOMEM;
		goto free_cfg;
	}
	vif = wilc_netdev_ifc_init(wl, "wlan%d", WILC_STATION_MODE,
				   NL80211_IFTYPE_STATION, false);
	if (IS_ERR(vif)) {
		ret = PTR_ERR(vif);
		goto free_hq;
	}

	wlan_init_locks(wl);

	return 0;

free_hq:
	destroy_workqueue(wl->hif_workqueue);

free_cfg:
	wilc_wlan_cfg_deinit(wl);

free_wl:
	wiphy_unregister(wl->wiphy);
	wiphy_free(wl->wiphy);
	return ret;
}