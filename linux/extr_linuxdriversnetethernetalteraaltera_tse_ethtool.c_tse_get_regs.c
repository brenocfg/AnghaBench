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
struct ethtool_regs {int version; } ;
struct altera_tse_private {int /*<<< orphan*/  mac_dev; } ;

/* Variables and functions */
 int TSE_NUM_REGS ; 
 int /*<<< orphan*/  csrrd32 (int /*<<< orphan*/ ,int) ; 
 struct altera_tse_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void tse_get_regs(struct net_device *dev, struct ethtool_regs *regs,
			 void *regbuf)
{
	int i;
	struct altera_tse_private *priv = netdev_priv(dev);
	u32 *buf = regbuf;

	/* Set version to a known value, so ethtool knows
	 * how to do any special formatting of this data.
	 * This version number will need to change if and
	 * when this register table is changed.
	 *
	 * version[31:0] = 1: Dump the first 128 TSE Registers
	 *      Upper bits are all 0 by default
	 *
	 * Upper 16-bits will indicate feature presence for
	 * Ethtool register decoding in future version.
	 */

	regs->version = 1;

	for (i = 0; i < TSE_NUM_REGS; i++)
		buf[i] = csrrd32(priv->mac_dev, i * 4);
}