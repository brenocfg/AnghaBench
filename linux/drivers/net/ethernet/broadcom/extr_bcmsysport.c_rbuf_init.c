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
struct bcm_sysport_priv {scalar_t__ is_lite; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CPU_BIG_ENDIAN ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int RBUF_4B_ALGN ; 
 int /*<<< orphan*/  RBUF_CONTROL ; 
 int RBUF_RSB_EN ; 
 int RBUF_RSB_SWAP0 ; 
 int RBUF_RSB_SWAP1 ; 
 int rbuf_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbuf_writel (struct bcm_sysport_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbuf_init(struct bcm_sysport_priv *priv)
{
	u32 reg;

	reg = rbuf_readl(priv, RBUF_CONTROL);
	reg |= RBUF_4B_ALGN | RBUF_RSB_EN;
	/* Set a correct RSB format on SYSTEMPORT Lite */
	if (priv->is_lite)
		reg &= ~RBUF_RSB_SWAP1;

	/* Set a correct RSB format based on host endian */
	if (!IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		reg |= RBUF_RSB_SWAP0;
	else
		reg &= ~RBUF_RSB_SWAP0;
	rbuf_writel(priv, reg, RBUF_CONTROL);
}