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
typedef  unsigned int u32 ;
struct net_device {int dummy; } ;
struct ftgmac100 {scalar_t__ base; struct net_device* netdev; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int FTGMAC100_MACCR_SW_RST ; 
 scalar_t__ FTGMAC100_OFFSET_MACCR ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ftgmac100_reset_mac(struct ftgmac100 *priv, u32 maccr)
{
	struct net_device *netdev = priv->netdev;
	int i;

	/* NOTE: reset clears all registers */
	iowrite32(maccr, priv->base + FTGMAC100_OFFSET_MACCR);
	iowrite32(maccr | FTGMAC100_MACCR_SW_RST,
		  priv->base + FTGMAC100_OFFSET_MACCR);
	for (i = 0; i < 200; i++) {
		unsigned int maccr;

		maccr = ioread32(priv->base + FTGMAC100_OFFSET_MACCR);
		if (!(maccr & FTGMAC100_MACCR_SW_RST))
			return 0;

		udelay(1);
	}

	netdev_err(netdev, "Hardware reset failed\n");
	return -EIO;
}