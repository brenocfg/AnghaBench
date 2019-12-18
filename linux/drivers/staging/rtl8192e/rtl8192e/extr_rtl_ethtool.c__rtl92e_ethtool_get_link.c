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
typedef  int u32 ;
struct r8192_priv {TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ RTLLIB_LINKED ; 
 scalar_t__ RTLLIB_LINKED_SCANNING ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static u32 _rtl92e_ethtool_get_link(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	return ((priv->rtllib->state == RTLLIB_LINKED) ||
		(priv->rtllib->state == RTLLIB_LINKED_SCANNING));
}