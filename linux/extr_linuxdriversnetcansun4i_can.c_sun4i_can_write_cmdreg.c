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
typedef  int /*<<< orphan*/  u8 ;
struct sun4ican_priv {int /*<<< orphan*/  cmdreg_lock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SUN4I_REG_CMD_ADDR ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sun4i_can_write_cmdreg(struct sun4ican_priv *priv, u8 val)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->cmdreg_lock, flags);
	writel(val, priv->base + SUN4I_REG_CMD_ADDR);
	spin_unlock_irqrestore(&priv->cmdreg_lock, flags);
}