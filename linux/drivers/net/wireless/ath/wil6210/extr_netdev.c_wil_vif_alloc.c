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
typedef  scalar_t__ u8 ;
struct wireless_dev {int iftype; struct net_device* netdev; int /*<<< orphan*/  wiphy; } ;
struct wil6210_vif {struct wireless_dev wdev; scalar_t__ mid; struct wil6210_priv* wil; struct net_device* ndev; } ;
struct wil6210_priv {int /*<<< orphan*/  wiphy; struct net_device* main_ndev; } ;
struct net_device {int needs_free_netdev; int hw_features; int features; struct wireless_dev* ieee80211_ptr; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  priv_destructor; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct wil6210_vif* ERR_PTR (int /*<<< orphan*/ ) ; 
 int NETIF_F_GRO ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ U8_MAX ; 
 struct net_device* alloc_netdev (int,char const*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 int /*<<< orphan*/  wil_dev_setup ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_ndev_destructor ; 
 int /*<<< orphan*/  wil_netdev_ops ; 
 int /*<<< orphan*/  wil_set_ethtoolops (struct net_device*) ; 
 int /*<<< orphan*/  wil_to_dev (struct wil6210_priv*) ; 
 scalar_t__ wil_vif_find_free_mid (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_vif_init (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wiphy_dev (int /*<<< orphan*/ ) ; 

struct wil6210_vif *
wil_vif_alloc(struct wil6210_priv *wil, const char *name,
	      unsigned char name_assign_type, enum nl80211_iftype iftype)
{
	struct net_device *ndev;
	struct wireless_dev *wdev;
	struct wil6210_vif *vif;
	u8 mid;

	mid = wil_vif_find_free_mid(wil);
	if (mid == U8_MAX) {
		wil_err(wil, "no available virtual interface\n");
		return ERR_PTR(-EINVAL);
	}

	ndev = alloc_netdev(sizeof(*vif), name, name_assign_type,
			    wil_dev_setup);
	if (!ndev) {
		dev_err(wil_to_dev(wil), "alloc_netdev failed\n");
		return ERR_PTR(-ENOMEM);
	}
	if (mid == 0) {
		wil->main_ndev = ndev;
	} else {
		ndev->priv_destructor = wil_ndev_destructor;
		ndev->needs_free_netdev = true;
	}

	vif = ndev_to_vif(ndev);
	vif->ndev = ndev;
	vif->wil = wil;
	vif->mid = mid;
	wil_vif_init(vif);

	wdev = &vif->wdev;
	wdev->wiphy = wil->wiphy;
	wdev->iftype = iftype;

	ndev->netdev_ops = &wil_netdev_ops;
	wil_set_ethtoolops(ndev);
	ndev->ieee80211_ptr = wdev;
	ndev->hw_features = NETIF_F_HW_CSUM | NETIF_F_RXCSUM |
			    NETIF_F_SG | NETIF_F_GRO |
			    NETIF_F_TSO | NETIF_F_TSO6;

	ndev->features |= ndev->hw_features;
	SET_NETDEV_DEV(ndev, wiphy_dev(wdev->wiphy));
	wdev->netdev = ndev;
	return vif;
}