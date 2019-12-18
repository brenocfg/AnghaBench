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
struct bcm_sysport_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_FLUSH ; 
 int /*<<< orphan*/  RX_FLUSH_CNTL ; 
 int /*<<< orphan*/  TX_FLUSH ; 
 int /*<<< orphan*/  TX_FLUSH_CNTL ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  topctrl_writel (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void topctrl_flush(struct bcm_sysport_priv *priv)
{
	topctrl_writel(priv, RX_FLUSH, RX_FLUSH_CNTL);
	topctrl_writel(priv, TX_FLUSH, TX_FLUSH_CNTL);
	mdelay(1);
	topctrl_writel(priv, 0, RX_FLUSH_CNTL);
	topctrl_writel(priv, 0, TX_FLUSH_CNTL);
}