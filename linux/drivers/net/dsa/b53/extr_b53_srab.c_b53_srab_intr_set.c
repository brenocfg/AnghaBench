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
struct b53_srab_priv {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ B53_SRAB_CTRLS ; 
 int /*<<< orphan*/  B53_SRAB_CTRLS_HOST_INTR ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void b53_srab_intr_set(struct b53_srab_priv *priv, bool set)
{
	u32 reg;

	reg = readl(priv->regs + B53_SRAB_CTRLS);
	if (set)
		reg |= B53_SRAB_CTRLS_HOST_INTR;
	else
		reg &= ~B53_SRAB_CTRLS_HOST_INTR;
	writel(reg, priv->regs + B53_SRAB_CTRLS);
}