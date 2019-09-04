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
struct input_dev {int dummy; } ;
struct da9052_tsi {int stopped; int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_IRQ_PENDOWN ; 
 int /*<<< orphan*/  DA9052_TSI_CONT_A_REG ; 
 int /*<<< orphan*/  da9052_enable_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int da9052_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct da9052_tsi* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static int da9052_ts_input_open(struct input_dev *input_dev)
{
	struct da9052_tsi *tsi = input_get_drvdata(input_dev);

	tsi->stopped = false;
	mb();

	/* Unmask PEN_DOWN event */
	da9052_enable_irq(tsi->da9052, DA9052_IRQ_PENDOWN);

	/* Enable Pen Detect Circuit */
	return da9052_reg_update(tsi->da9052, DA9052_TSI_CONT_A_REG,
				 1 << 1, 1 << 1);
}