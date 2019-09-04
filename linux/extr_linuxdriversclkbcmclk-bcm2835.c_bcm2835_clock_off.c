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
struct clk_hw {int dummy; } ;
struct bcm2835_cprman {int /*<<< orphan*/  regs_lock; } ;
struct bcm2835_clock_data {int /*<<< orphan*/  ctl_reg; } ;
struct bcm2835_clock {struct bcm2835_clock_data* data; struct bcm2835_cprman* cprman; } ;

/* Variables and functions */
 int CM_ENABLE ; 
 struct bcm2835_clock* bcm2835_clock_from_hw (struct clk_hw*) ; 
 int /*<<< orphan*/  bcm2835_clock_wait_busy (struct bcm2835_clock*) ; 
 int cprman_read (struct bcm2835_cprman*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cprman_write (struct bcm2835_cprman*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm2835_clock_off(struct clk_hw *hw)
{
	struct bcm2835_clock *clock = bcm2835_clock_from_hw(hw);
	struct bcm2835_cprman *cprman = clock->cprman;
	const struct bcm2835_clock_data *data = clock->data;

	spin_lock(&cprman->regs_lock);
	cprman_write(cprman, data->ctl_reg,
		     cprman_read(cprman, data->ctl_reg) & ~CM_ENABLE);
	spin_unlock(&cprman->regs_lock);

	/* BUSY will remain high until the divider completes its cycle. */
	bcm2835_clock_wait_busy(clock);
}