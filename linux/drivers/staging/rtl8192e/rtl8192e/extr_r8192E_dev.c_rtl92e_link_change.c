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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ bPromiscuousOn; } ;
struct rtllib_device {scalar_t__ state; scalar_t__ pairwise_key_type; scalar_t__ iw_mode; TYPE_2__ IntelPromiscuousModeInfo; } ;
struct r8192_priv {int ReceiveConfig; struct rtllib_device* rtllib; TYPE_1__* ops; int /*<<< orphan*/  up; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_ratr_table ) (struct net_device*) ;} ;

/* Variables and functions */
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ KEY_TYPE_WEP104 ; 
 scalar_t__ KEY_TYPE_WEP40 ; 
 int /*<<< orphan*/  RCR ; 
 int /*<<< orphan*/  RCR_CBSSID ; 
 scalar_t__ RTLLIB_LINKED ; 
 int /*<<< orphan*/  _rtl92e_net_update (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_update_msr (struct net_device*) ; 
 int /*<<< orphan*/  rtl92e_enable_hw_security_config (struct net_device*) ; 
 int /*<<< orphan*/  rtl92e_readl (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92e_writel (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

void rtl92e_link_change(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	struct rtllib_device *ieee = priv->rtllib;

	if (!priv->up)
		return;

	if (ieee->state == RTLLIB_LINKED) {
		_rtl92e_net_update(dev);
		priv->ops->update_ratr_table(dev);
		if ((ieee->pairwise_key_type == KEY_TYPE_WEP40) ||
		    (ieee->pairwise_key_type == KEY_TYPE_WEP104))
			rtl92e_enable_hw_security_config(dev);
	} else {
		rtl92e_writeb(dev, 0x173, 0);
	}
	_rtl92e_update_msr(dev);

	if (ieee->iw_mode == IW_MODE_INFRA || ieee->iw_mode == IW_MODE_ADHOC) {
		u32 reg;

		reg = rtl92e_readl(dev, RCR);
		if (priv->rtllib->state == RTLLIB_LINKED) {
			if (ieee->IntelPromiscuousModeInfo.bPromiscuousOn)
				;
			else
				priv->ReceiveConfig = reg |= RCR_CBSSID;
		} else
			priv->ReceiveConfig = reg &= ~RCR_CBSSID;

		rtl92e_writel(dev, RCR, reg);
	}
}