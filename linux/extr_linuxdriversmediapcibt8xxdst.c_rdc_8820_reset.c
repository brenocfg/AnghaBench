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
 int /*<<< orphan*/  DELAY ; 
 int /*<<< orphan*/  NO_DELAY ; 
 int /*<<< orphan*/  RDC_8820_RESET ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 scalar_t__ dst_gpio_outb (struct dst_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rdc_8820_reset(struct dst_state *state)
{
	dprintk(3, "Resetting DST\n");
	if (dst_gpio_outb(state, RDC_8820_RESET, RDC_8820_RESET, 0, NO_DELAY) < 0) {
		pr_err("dst_gpio_outb ERROR !\n");
		return -1;
	}
	udelay(1000);
	if (dst_gpio_outb(state, RDC_8820_RESET, RDC_8820_RESET, RDC_8820_RESET, DELAY) < 0) {
		pr_err("dst_gpio_outb ERROR !\n");
		return -1;
	}

	return 0;
}