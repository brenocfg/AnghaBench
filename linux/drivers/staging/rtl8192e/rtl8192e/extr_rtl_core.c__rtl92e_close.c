#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct r8192_priv {int /*<<< orphan*/  wx_mutex; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int softmac_features; } ;

/* Variables and functions */
 int IEEE_SOFTMAC_SCAN ; 
 int _rtl92e_down (struct net_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rtllib_act_scanning (TYPE_1__*,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtllib_stop_scan (TYPE_1__*) ; 

__attribute__((used)) static int _rtl92e_close(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	int ret;

	if ((rtllib_act_scanning(priv->rtllib, false)) &&
		!(priv->rtllib->softmac_features & IEEE_SOFTMAC_SCAN)) {
		rtllib_stop_scan(priv->rtllib);
	}

	mutex_lock(&priv->wx_mutex);

	ret = _rtl92e_down(dev, true);

	mutex_unlock(&priv->wx_mutex);

	return ret;

}