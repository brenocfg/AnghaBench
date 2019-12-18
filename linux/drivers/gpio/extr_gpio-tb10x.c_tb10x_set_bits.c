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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  bgpio_lock; } ;
struct tb10x_gpio {TYPE_1__ gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tb10x_reg_read (struct tb10x_gpio*,unsigned int) ; 
 int /*<<< orphan*/  tb10x_reg_write (struct tb10x_gpio*,unsigned int,int) ; 

__attribute__((used)) static inline void tb10x_set_bits(struct tb10x_gpio *gpio, unsigned int offs,
				u32 mask, u32 val)
{
	u32 r;
	unsigned long flags;

	spin_lock_irqsave(&gpio->gc.bgpio_lock, flags);

	r = tb10x_reg_read(gpio, offs);
	r = (r & ~mask) | (val & mask);

	tb10x_reg_write(gpio, offs, r);

	spin_unlock_irqrestore(&gpio->gc.bgpio_lock, flags);
}