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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct nb8800_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NB8800_STAT_DATA ; 
 int /*<<< orphan*/  NB8800_STAT_INDEX ; 
 int /*<<< orphan*/  nb8800_readl (struct nb8800_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb8800_writeb (struct nb8800_priv*,int /*<<< orphan*/ ,int) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 nb8800_read_stat(struct net_device *dev, int index)
{
	struct nb8800_priv *priv = netdev_priv(dev);

	nb8800_writeb(priv, NB8800_STAT_INDEX, index);

	return nb8800_readl(priv, NB8800_STAT_DATA);
}