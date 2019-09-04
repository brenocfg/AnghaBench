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
struct pch_can_priv {TYPE_1__* regs; } ;
struct net_device {int dummy; } ;
struct can_berr_counter {int txerr; int rxerr; } ;
struct TYPE_2__ {int /*<<< orphan*/  errc; } ;

/* Variables and functions */
 int PCH_REC ; 
 int PCH_TEC ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 struct pch_can_priv* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int pch_can_get_berr_counter(const struct net_device *dev,
				    struct can_berr_counter *bec)
{
	struct pch_can_priv *priv = netdev_priv(dev);
	u32 errc = ioread32(&priv->regs->errc);

	bec->txerr = errc & PCH_TEC;
	bec->rxerr = (errc & PCH_REC) >> 8;

	return 0;
}