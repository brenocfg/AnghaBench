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
struct bcm_sysport_priv {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  RDMA_CONTROL ; 
 int RDMA_DISABLED ; 
 int RDMA_EN ; 
 int /*<<< orphan*/  RDMA_STATUS ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int rdma_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_writel (struct bcm_sysport_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline int rdma_enable_set(struct bcm_sysport_priv *priv,
				  unsigned int enable)
{
	unsigned int timeout = 1000;
	u32 reg;

	reg = rdma_readl(priv, RDMA_CONTROL);
	if (enable)
		reg |= RDMA_EN;
	else
		reg &= ~RDMA_EN;
	rdma_writel(priv, reg, RDMA_CONTROL);

	/* Poll for RMDA disabling completion */
	do {
		reg = rdma_readl(priv, RDMA_STATUS);
		if (!!(reg & RDMA_DISABLED) == !enable)
			return 0;
		usleep_range(1000, 2000);
	} while (timeout-- > 0);

	netdev_err(priv->netdev, "timeout waiting for RDMA to finish\n");

	return -ETIMEDOUT;
}