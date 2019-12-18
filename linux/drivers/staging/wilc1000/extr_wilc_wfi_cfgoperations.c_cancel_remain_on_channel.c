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
typedef  scalar_t__ u64 ;
struct wireless_dev {int /*<<< orphan*/  netdev; } ;
struct wiphy {int dummy; } ;
struct TYPE_2__ {scalar_t__ listen_cookie; } ;
struct wilc_priv {TYPE_1__ remain_on_ch_params; } ;
struct wilc_vif {struct wilc_priv priv; } ;

/* Variables and functions */
 int ENOENT ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int wilc_listen_state_expired (struct wilc_vif*,scalar_t__) ; 

__attribute__((used)) static int cancel_remain_on_channel(struct wiphy *wiphy,
				    struct wireless_dev *wdev,
				    u64 cookie)
{
	struct wilc_vif *vif = netdev_priv(wdev->netdev);
	struct wilc_priv *priv = &vif->priv;

	if (cookie != priv->remain_on_ch_params.listen_cookie)
		return -ENOENT;

	return wilc_listen_state_expired(vif, cookie);
}