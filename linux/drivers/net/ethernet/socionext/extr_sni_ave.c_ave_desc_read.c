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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ daddr; } ;
struct TYPE_3__ {scalar_t__ daddr; } ;
struct ave_private {int desc_size; scalar_t__ base; TYPE_2__ rx; TYPE_1__ tx; } ;
typedef  enum desc_id { ____Placeholder_desc_id } desc_id ;

/* Variables and functions */
 int AVE_DESCID_TX ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static u32 ave_desc_read(struct net_device *ndev, enum desc_id id, int entry,
			 int offset)
{
	struct ave_private *priv = netdev_priv(ndev);
	u32 addr;

	addr = ((id == AVE_DESCID_TX) ? priv->tx.daddr : priv->rx.daddr)
		+ entry * priv->desc_size + offset;

	return readl(priv->base + addr);
}