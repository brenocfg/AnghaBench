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
struct gpmi_nand_data {int /*<<< orphan*/  bch_done; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpmi_clear_bch (struct gpmi_nand_data*) ; 

__attribute__((used)) static irqreturn_t bch_irq(int irq, void *cookie)
{
	struct gpmi_nand_data *this = cookie;

	gpmi_clear_bch(this);
	complete(&this->bch_done);
	return IRQ_HANDLED;
}