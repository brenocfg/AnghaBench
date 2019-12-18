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
struct rcar_thermal_priv {struct rcar_thermal_common* common; } ;
struct rcar_thermal_common {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTMSK ; 
 int /*<<< orphan*/  rcar_has_irq_support (struct rcar_thermal_priv*) ; 
 int rcar_id_to_shift (struct rcar_thermal_priv*) ; 
 int /*<<< orphan*/  rcar_thermal_common_bset (struct rcar_thermal_common*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void _rcar_thermal_irq_ctrl(struct rcar_thermal_priv *priv, int enable)
{
	struct rcar_thermal_common *common = priv->common;
	unsigned long flags;
	u32 mask = 0x3 << rcar_id_to_shift(priv); /* enable Rising/Falling */

	if (!rcar_has_irq_support(priv))
		return;

	spin_lock_irqsave(&common->lock, flags);

	rcar_thermal_common_bset(common, INTMSK, mask, enable ? 0 : mask);

	spin_unlock_irqrestore(&common->lock, flags);
}