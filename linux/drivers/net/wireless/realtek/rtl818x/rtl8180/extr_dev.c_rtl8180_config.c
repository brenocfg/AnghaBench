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
typedef  int /*<<< orphan*/  u32 ;
struct rtl8180_priv {TYPE_1__* rf; } ;
struct ieee80211_conf {int dummy; } ;
struct ieee80211_hw {struct ieee80211_conf conf; struct rtl8180_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_chan ) (struct ieee80211_hw*,struct ieee80211_conf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,struct ieee80211_conf*) ; 

__attribute__((used)) static int rtl8180_config(struct ieee80211_hw *dev, u32 changed)
{
	struct rtl8180_priv *priv = dev->priv;
	struct ieee80211_conf *conf = &dev->conf;

	priv->rf->set_chan(dev, conf);

	return 0;
}