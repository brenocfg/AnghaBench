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
struct altera_tse_private {int /*<<< orphan*/  mac_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  csrwr32 (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hash_table ; 
 struct altera_tse_private* netdev_priv (struct net_device*) ; 
 scalar_t__ tse_csroffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void altera_tse_set_mcfilterall(struct net_device *dev)
{
	struct altera_tse_private *priv = netdev_priv(dev);
	int i;

	/* set the hash filter */
	for (i = 0; i < 64; i++)
		csrwr32(1, priv->mac_dev, tse_csroffs(hash_table) + i * 4);
}