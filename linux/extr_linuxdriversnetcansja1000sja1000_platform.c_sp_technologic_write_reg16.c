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
typedef  int u8 ;
struct technologic_priv {int /*<<< orphan*/  io_lock; } ;
struct sja1000_priv {scalar_t__ reg_base; struct technologic_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sp_technologic_write_reg16(const struct sja1000_priv *priv,
				       int reg, u8 val)
{
	struct technologic_priv *tp = priv->priv;
	unsigned long flags;

	spin_lock_irqsave(&tp->io_lock, flags);
	iowrite16(reg, priv->reg_base + 0);
	iowrite16(val, priv->reg_base + 2);
	spin_unlock_irqrestore(&tp->io_lock, flags);
}