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
typedef  int /*<<< orphan*/  u8 ;
struct sja1000_priv {TYPE_1__* dev; scalar_t__ reg_base; } ;
struct TYPE_2__ {size_t dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  inb (unsigned long) ; 
 int /*<<< orphan*/ * indirect_lock ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u8 sja1000_isa_port_read_reg_indirect(const struct sja1000_priv *priv,
					     int reg)
{
	unsigned long flags, base = (unsigned long)priv->reg_base;
	u8 readval;

	spin_lock_irqsave(&indirect_lock[priv->dev->dev_id], flags);
	outb(reg, base);
	readval = inb(base + 1);
	spin_unlock_irqrestore(&indirect_lock[priv->dev->dev_id], flags);

	return readval;
}