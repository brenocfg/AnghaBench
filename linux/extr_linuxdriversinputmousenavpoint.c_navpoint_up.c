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
struct ssp_device {int /*<<< orphan*/  clk; } ;
struct navpoint {int /*<<< orphan*/  gpio; int /*<<< orphan*/  dev; struct ssp_device* ssp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSCR0 ; 
 int /*<<< orphan*/  SSCR1 ; 
 int /*<<< orphan*/  SSSR ; 
 int SSSR_CSS ; 
 int /*<<< orphan*/  SSTO ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pxa_ssp_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_ssp_write_reg (struct ssp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscr0 ; 
 int /*<<< orphan*/  sscr1 ; 
 int /*<<< orphan*/  sssr ; 

__attribute__((used)) static void navpoint_up(struct navpoint *navpoint)
{
	struct ssp_device *ssp = navpoint->ssp;
	int timeout;

	clk_prepare_enable(ssp->clk);

	pxa_ssp_write_reg(ssp, SSCR1, sscr1);
	pxa_ssp_write_reg(ssp, SSSR, sssr);
	pxa_ssp_write_reg(ssp, SSTO, 0);
	pxa_ssp_write_reg(ssp, SSCR0, sscr0);	/* SSCR0_SSE written last */

	/* Wait until SSP port is ready for slave clock operations */
	for (timeout = 100; timeout != 0; --timeout) {
		if (!(pxa_ssp_read_reg(ssp, SSSR) & SSSR_CSS))
			break;
		msleep(1);
	}

	if (timeout == 0)
		dev_err(navpoint->dev,
			"timeout waiting for SSSR[CSS] to clear\n");

	if (gpio_is_valid(navpoint->gpio))
		gpio_set_value(navpoint->gpio, 1);
}