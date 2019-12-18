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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ave_private {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ AVE_PFEN ; 
 unsigned int AVE_PF_SIZE ; 
 int BIT (unsigned int) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ave_pfsel_start(struct net_device *ndev, unsigned int entry)
{
	struct ave_private *priv = netdev_priv(ndev);
	u32 val;

	if (WARN_ON(entry > AVE_PF_SIZE))
		return -EINVAL;

	val = readl(priv->base + AVE_PFEN);
	writel(val | BIT(entry), priv->base + AVE_PFEN);

	return 0;
}