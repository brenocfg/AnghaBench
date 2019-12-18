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
struct at91_udc {int clocked; int /*<<< orphan*/  fclk; int /*<<< orphan*/  iclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_on(struct at91_udc *udc)
{
	if (udc->clocked)
		return;
	udc->clocked = 1;

	clk_enable(udc->iclk);
	clk_enable(udc->fclk);
}