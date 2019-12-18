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
struct net_device {int dummy; } ;
struct cc770_priv {int dummy; } ;
struct can_berr_counter {void* rxerr; void* txerr; } ;

/* Variables and functions */
 void* cc770_read_reg (struct cc770_priv*,int /*<<< orphan*/ ) ; 
 struct cc770_priv* netdev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  rx_error_counter ; 
 int /*<<< orphan*/  tx_error_counter ; 

__attribute__((used)) static int cc770_get_berr_counter(const struct net_device *dev,
				  struct can_berr_counter *bec)
{
	struct cc770_priv *priv = netdev_priv(dev);

	bec->txerr = cc770_read_reg(priv, tx_error_counter);
	bec->rxerr = cc770_read_reg(priv, rx_error_counter);

	return 0;
}