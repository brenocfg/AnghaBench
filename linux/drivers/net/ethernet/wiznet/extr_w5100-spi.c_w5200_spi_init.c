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
struct w5200_spi_priv {int /*<<< orphan*/  cmd_lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct w5200_spi_priv* w5200_spi_priv (struct net_device*) ; 

__attribute__((used)) static int w5200_spi_init(struct net_device *ndev)
{
	struct w5200_spi_priv *spi_priv = w5200_spi_priv(ndev);

	mutex_init(&spi_priv->cmd_lock);

	return 0;
}