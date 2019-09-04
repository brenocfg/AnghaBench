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
struct ftmac100 {scalar_t__ base; struct net_device* netdev; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int FTMAC100_MACCR_SW_RST ; 
 scalar_t__ FTMAC100_OFFSET_MACCR ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ftmac100_reset(struct ftmac100 *priv)
{
	struct net_device *netdev = priv->netdev;
	int i;

	/* NOTE: reset clears all registers */
	iowrite32(FTMAC100_MACCR_SW_RST, priv->base + FTMAC100_OFFSET_MACCR);

	for (i = 0; i < 5; i++) {
		unsigned int maccr;

		maccr = ioread32(priv->base + FTMAC100_OFFSET_MACCR);
		if (!(maccr & FTMAC100_MACCR_SW_RST)) {
			/*
			 * FTMAC100_MACCR_SW_RST cleared does not indicate
			 * that hardware reset completed (what the f*ck).
			 * We still need to wait for a while.
			 */
			udelay(500);
			return 0;
		}

		udelay(1000);
	}

	netdev_err(netdev, "software reset failed\n");
	return -EIO;
}