#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct r8192_priv {TYPE_1__* rtllib; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IMR_RDU ; 
 int /*<<< orphan*/  INTA_MASK ; 
 int /*<<< orphan*/  _rtl92e_rx_normal (int /*<<< orphan*/ ) ; 
 int rtl92e_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl92e_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92e_irq_rx_tasklet(struct r8192_priv *priv)
{
	_rtl92e_rx_normal(priv->rtllib->dev);

	rtl92e_writel(priv->rtllib->dev, INTA_MASK,
		      rtl92e_readl(priv->rtllib->dev, INTA_MASK) | IMR_RDU);
}