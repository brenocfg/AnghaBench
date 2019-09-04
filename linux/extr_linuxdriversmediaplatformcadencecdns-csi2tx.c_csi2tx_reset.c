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
struct csi2tx_priv {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CSI2TX_CONFIG_REG ; 
 int /*<<< orphan*/  CSI2TX_CONFIG_SRST_REQ ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void csi2tx_reset(struct csi2tx_priv *csi2tx)
{
	writel(CSI2TX_CONFIG_SRST_REQ, csi2tx->base + CSI2TX_CONFIG_REG);

	udelay(10);
}