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
typedef  enum desc_state { ____Placeholder_desc_state } desc_state ;

/* Variables and functions */
 scalar_t__ AVE_DESCC ; 
 int AVE_DESCC_RD0 ; 
 int AVE_DESCC_RDSTP ; 
 int AVE_DESCC_STATUS_MASK ; 
 int AVE_DESCC_TD ; 
#define  AVE_DESC_RX_PERMIT 131 
#define  AVE_DESC_RX_SUSPEND 130 
#define  AVE_DESC_START 129 
#define  AVE_DESC_STOP 128 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ave_desc_switch(struct net_device *ndev, enum desc_state state)
{
	struct ave_private *priv = netdev_priv(ndev);
	int ret = 0;
	u32 val;

	switch (state) {
	case AVE_DESC_START:
		writel(AVE_DESCC_TD | AVE_DESCC_RD0, priv->base + AVE_DESCC);
		break;

	case AVE_DESC_STOP:
		writel(0, priv->base + AVE_DESCC);
		if (readl_poll_timeout(priv->base + AVE_DESCC, val, !val,
				       150, 15000)) {
			netdev_err(ndev, "can't stop descriptor\n");
			ret = -EBUSY;
		}
		break;

	case AVE_DESC_RX_SUSPEND:
		val = readl(priv->base + AVE_DESCC);
		val |= AVE_DESCC_RDSTP;
		val &= ~AVE_DESCC_STATUS_MASK;
		writel(val, priv->base + AVE_DESCC);
		if (readl_poll_timeout(priv->base + AVE_DESCC, val,
				       val & (AVE_DESCC_RDSTP << 16),
				       150, 150000)) {
			netdev_err(ndev, "can't suspend descriptor\n");
			ret = -EBUSY;
		}
		break;

	case AVE_DESC_RX_PERMIT:
		val = readl(priv->base + AVE_DESCC);
		val &= ~AVE_DESCC_RDSTP;
		val &= ~AVE_DESCC_STATUS_MASK;
		writel(val, priv->base + AVE_DESCC);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}