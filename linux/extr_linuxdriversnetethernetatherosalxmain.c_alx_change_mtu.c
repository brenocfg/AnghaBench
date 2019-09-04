#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int mtu; } ;
struct TYPE_2__ {int mtu; } ;
struct alx_priv {int /*<<< orphan*/  rxbuf_size; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_DEF_RXBUF_SIZE ; 
 int ALX_MAX_FRAME_LEN (int) ; 
 int /*<<< orphan*/  alx_reinit (struct alx_priv*) ; 
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 struct alx_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int alx_change_mtu(struct net_device *netdev, int mtu)
{
	struct alx_priv *alx = netdev_priv(netdev);
	int max_frame = ALX_MAX_FRAME_LEN(mtu);

	netdev->mtu = mtu;
	alx->hw.mtu = mtu;
	alx->rxbuf_size = max(max_frame, ALX_DEF_RXBUF_SIZE);
	netdev_update_features(netdev);
	if (netif_running(netdev))
		alx_reinit(alx);
	return 0;
}