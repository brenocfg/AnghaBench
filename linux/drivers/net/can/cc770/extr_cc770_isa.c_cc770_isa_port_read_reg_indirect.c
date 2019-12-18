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
struct cc770_priv {scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cc770_isa_port_lock ; 
 int /*<<< orphan*/  inb (unsigned long) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u8 cc770_isa_port_read_reg_indirect(const struct cc770_priv *priv,
					     int reg)
{
	unsigned long base = (unsigned long)priv->reg_base;
	unsigned long flags;
	u8 val;

	spin_lock_irqsave(&cc770_isa_port_lock, flags);
	outb(reg, base);
	val = inb(base + 1);
	spin_unlock_irqrestore(&cc770_isa_port_lock, flags);

	return val;
}