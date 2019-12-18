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
struct spi_device {int dummy; } ;
struct net_device {int dummy; } ;
struct hi3110_priv {int /*<<< orphan*/  hi3110_lock; struct spi_device* spi; } ;
struct can_berr_counter {void* rxerr; void* txerr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HI3110_READ_REC ; 
 int /*<<< orphan*/  HI3110_READ_TEC ; 
 void* hi3110_read (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hi3110_priv* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int hi3110_get_berr_counter(const struct net_device *net,
				   struct can_berr_counter *bec)
{
	struct hi3110_priv *priv = netdev_priv(net);
	struct spi_device *spi = priv->spi;

	mutex_lock(&priv->hi3110_lock);
	bec->txerr = hi3110_read(spi, HI3110_READ_TEC);
	bec->rxerr = hi3110_read(spi, HI3110_READ_REC);
	mutex_unlock(&priv->hi3110_lock);

	return 0;
}