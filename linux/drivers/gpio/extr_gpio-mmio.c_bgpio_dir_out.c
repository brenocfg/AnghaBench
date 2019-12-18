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
struct gpio_chip {int /*<<< orphan*/  bgpio_lock; int /*<<< orphan*/  bgpio_dir; scalar_t__ reg_dir_out; int /*<<< orphan*/  (* write_reg ) (scalar_t__,int /*<<< orphan*/ ) ;scalar_t__ reg_dir_in; int /*<<< orphan*/  (* set ) (struct gpio_chip*,unsigned int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bgpio_line2mask (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bgpio_dir_out(struct gpio_chip *gc, unsigned int gpio, int val)
{
	unsigned long flags;

	gc->set(gc, gpio, val);

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	gc->bgpio_dir |= bgpio_line2mask(gc, gpio);

	if (gc->reg_dir_in)
		gc->write_reg(gc->reg_dir_in, ~gc->bgpio_dir);
	if (gc->reg_dir_out)
		gc->write_reg(gc->reg_dir_out, gc->bgpio_dir);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	return 0;
}