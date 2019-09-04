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
struct hix5hd2_priv {scalar_t__ base; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_RX_FQ_START_ADDR_EN ; 
 scalar_t__ RX_FQ_REG_EN ; 
 scalar_t__ RX_FQ_START_ADDR ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hix5hd2_set_rx_fq(struct hix5hd2_priv *priv, dma_addr_t phy_addr)
{
	writel_relaxed(BITS_RX_FQ_START_ADDR_EN, priv->base + RX_FQ_REG_EN);
	writel_relaxed(phy_addr, priv->base + RX_FQ_START_ADDR);
	writel_relaxed(0, priv->base + RX_FQ_REG_EN);
}