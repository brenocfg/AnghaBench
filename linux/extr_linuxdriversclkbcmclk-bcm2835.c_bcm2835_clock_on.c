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
struct bcm2835_cprman {int /*<<< orphan*/  dev; int /*<<< orphan*/  regs_lock; } ;
struct bcm2835_clock_data {scalar_t__ tcnt_mux; int /*<<< orphan*/  name; int /*<<< orphan*/  ctl_reg; } ;
struct bcm2835_clock {struct bcm2835_clock_data* data; struct bcm2835_cprman* cprman; } ;

/* Variables and functions */
 int CM_ENABLE ; 
 int CM_GATE ; 
 struct bcm2835_clock* bcm2835_clock_from_hw (struct clk_hw*) ; 
 int /*<<< orphan*/  bcm2835_measure_tcnt_mux (struct bcm2835_cprman*,scalar_t__) ; 
 int /*<<< orphan*/  clk_hw_get_rate (struct clk_hw*) ; 
 int cprman_read (struct bcm2835_cprman*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cprman_write (struct bcm2835_cprman*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2835_clock_on(struct clk_hw *hw)
{
	struct bcm2835_clock *clock = bcm2835_clock_from_hw(hw);
	struct bcm2835_cprman *cprman = clock->cprman;
	const struct bcm2835_clock_data *data = clock->data;

	spin_lock(&cprman->regs_lock);
	cprman_write(cprman, data->ctl_reg,
		     cprman_read(cprman, data->ctl_reg) |
		     CM_ENABLE |
		     CM_GATE);
	spin_unlock(&cprman->regs_lock);

	/* Debug code to measure the clock once it's turned on to see
	 * if it's ticking at the rate we expect.
	 */
	if (data->tcnt_mux && false) {
		dev_info(cprman->dev,
			 "clk %s: rate %ld, measure %ld\n",
			 data->name,
			 clk_hw_get_rate(hw),
			 bcm2835_measure_tcnt_mux(cprman, data->tcnt_mux));
	}

	return 0;
}