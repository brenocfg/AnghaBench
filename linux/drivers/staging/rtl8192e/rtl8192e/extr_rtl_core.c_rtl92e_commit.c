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
struct r8192_priv {scalar_t__ up; TYPE_1__* ops; int /*<<< orphan*/  rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop_adapter ) (struct net_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl92e_up (struct net_device*,int) ; 
 int /*<<< orphan*/  rtl92e_irq_disable (struct net_device*) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtllib_softmac_stop_protocol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int) ; 

void rtl92e_commit(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	if (priv->up == 0)
		return;
	rtllib_softmac_stop_protocol(priv->rtllib, 0, true);
	rtl92e_irq_disable(dev);
	priv->ops->stop_adapter(dev, true);
	_rtl92e_up(dev, false);
}