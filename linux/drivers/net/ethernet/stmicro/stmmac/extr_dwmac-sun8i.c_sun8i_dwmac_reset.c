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
struct stmmac_priv {int /*<<< orphan*/  device; scalar_t__ ioaddr; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ EMAC_BASIC_CTL1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sun8i_dwmac_reset(struct stmmac_priv *priv)
{
	u32 v;
	int err;

	v = readl(priv->ioaddr + EMAC_BASIC_CTL1);
	writel(v | 0x01, priv->ioaddr + EMAC_BASIC_CTL1);

	/* The timeout was previoulsy set to 10ms, but some board (OrangePI0)
	 * need more if no cable plugged. 100ms seems OK
	 */
	err = readl_poll_timeout(priv->ioaddr + EMAC_BASIC_CTL1, v,
				 !(v & 0x01), 100, 100000);

	if (err) {
		dev_err(priv->device, "EMAC reset timeout\n");
		return -EFAULT;
	}
	return 0;
}