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
struct r8192_priv {int bcurrent_turbo_EDCA; int bis_cur_rdlstate; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int bis_any_nonbepkts; } ;

/* Variables and functions */
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

void rtl92e_dm_init_edca_turbo(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	priv->bcurrent_turbo_EDCA = false;
	priv->rtllib->bis_any_nonbepkts = false;
	priv->bis_cur_rdlstate = false;
}