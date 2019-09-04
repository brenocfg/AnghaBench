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
struct bt_bmc {int /*<<< orphan*/  queue; scalar_t__ offset; int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ BT_CR2 ; 
 int BT_CR2_IRQ_H2B ; 
 int BT_CR2_IRQ_HBUSY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bt_bmc_irq(int irq, void *arg)
{
	struct bt_bmc *bt_bmc = arg;
	u32 reg;
	int rc;

	rc = regmap_read(bt_bmc->map, bt_bmc->offset + BT_CR2, &reg);
	if (rc)
		return IRQ_NONE;

	reg &= BT_CR2_IRQ_H2B | BT_CR2_IRQ_HBUSY;
	if (!reg)
		return IRQ_NONE;

	/* ack pending IRQs */
	regmap_write(bt_bmc->map, bt_bmc->offset + BT_CR2, reg);

	wake_up(&bt_bmc->queue);
	return IRQ_HANDLED;
}