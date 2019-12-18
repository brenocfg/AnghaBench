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
struct ti_hecc_priv {int dummy; } ;
struct net_device {int dummy; } ;
struct can_berr_counter {void* rxerr; void* txerr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HECC_CANREC ; 
 int /*<<< orphan*/  HECC_CANTEC ; 
 void* hecc_read (struct ti_hecc_priv*,int /*<<< orphan*/ ) ; 
 struct ti_hecc_priv* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int ti_hecc_get_berr_counter(const struct net_device *ndev,
				    struct can_berr_counter *bec)
{
	struct ti_hecc_priv *priv = netdev_priv(ndev);

	bec->txerr = hecc_read(priv, HECC_CANTEC);
	bec->rxerr = hecc_read(priv, HECC_CANREC);

	return 0;
}