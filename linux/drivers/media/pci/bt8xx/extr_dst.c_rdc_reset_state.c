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
struct dst_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_DELAY ; 
 int /*<<< orphan*/  RDC_8820_INT ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 scalar_t__ dst_gpio_outb (struct dst_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int rdc_reset_state(struct dst_state *state)
{
	dprintk(2, "Resetting state machine\n");
	if (dst_gpio_outb(state, RDC_8820_INT, RDC_8820_INT, 0, NO_DELAY) < 0) {
		pr_err("dst_gpio_outb ERROR !\n");
		return -1;
	}
	msleep(10);
	if (dst_gpio_outb(state, RDC_8820_INT, RDC_8820_INT, RDC_8820_INT, NO_DELAY) < 0) {
		pr_err("dst_gpio_outb ERROR !\n");
		msleep(10);
		return -1;
	}

	return 0;
}