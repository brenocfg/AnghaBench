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
struct r8192_priv {int /*<<< orphan*/  ReceiveConfig; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCR ; 
 int /*<<< orphan*/  RCR_AAP ; 
 int /*<<< orphan*/  rtl92e_writel (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

void rtl92e_set_monitor_mode(struct net_device *dev, bool bAllowAllDA,
			     bool WriteIntoReg)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	if (bAllowAllDA)
		priv->ReceiveConfig |= RCR_AAP;
	else
		priv->ReceiveConfig &= ~RCR_AAP;

	if (WriteIntoReg)
		rtl92e_writel(dev, RCR, priv->ReceiveConfig);
}