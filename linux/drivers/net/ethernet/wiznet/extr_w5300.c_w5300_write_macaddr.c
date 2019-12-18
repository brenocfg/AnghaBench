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
struct w5300_priv {struct net_device* ndev; } ;
struct net_device {int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  W5300_SHARH ; 
 int /*<<< orphan*/  W5300_SHARL ; 
 int /*<<< orphan*/  w5300_write (struct w5300_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w5300_write32 (struct w5300_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void w5300_write_macaddr(struct w5300_priv *priv)
{
	struct net_device *ndev = priv->ndev;
	w5300_write32(priv, W5300_SHARL,
		      ndev->dev_addr[0] << 24 |
		      ndev->dev_addr[1] << 16 |
		      ndev->dev_addr[2] << 8 |
		      ndev->dev_addr[3]);
	w5300_write(priv, W5300_SHARH,
		      ndev->dev_addr[4] << 8 |
		      ndev->dev_addr[5]);
}