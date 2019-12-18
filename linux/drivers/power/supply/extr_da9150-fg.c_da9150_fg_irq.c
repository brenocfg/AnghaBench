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
typedef  int u32 ;
struct da9150_fg {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DA9150_FG_IRQ_SOC_MASK ; 
 int /*<<< orphan*/  DA9150_QIF_E_FG_STATUS ; 
 int /*<<< orphan*/  DA9150_QIF_E_FG_STATUS_SIZE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int da9150_fg_read_attr (struct da9150_fg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9150_fg_soc_event_config (struct da9150_fg*) ; 
 int /*<<< orphan*/  da9150_fg_write_attr (struct da9150_fg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t da9150_fg_irq(int irq, void *data)
{
	struct da9150_fg *fg = data;
	u32 e_fg_status;

	/* Read FG IRQ status info */
	e_fg_status = da9150_fg_read_attr(fg, DA9150_QIF_E_FG_STATUS,
					  DA9150_QIF_E_FG_STATUS_SIZE);

	/* Handle warning/critical threhold events */
	if (e_fg_status & DA9150_FG_IRQ_SOC_MASK)
		da9150_fg_soc_event_config(fg);

	/* Clear any FG IRQs */
	da9150_fg_write_attr(fg, DA9150_QIF_E_FG_STATUS,
			     DA9150_QIF_E_FG_STATUS_SIZE, e_fg_status);

	return IRQ_HANDLED;
}