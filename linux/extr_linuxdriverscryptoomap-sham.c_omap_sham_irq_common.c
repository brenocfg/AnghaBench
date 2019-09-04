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
struct omap_sham_dev {int /*<<< orphan*/  done_task; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_BUSY ; 
 int /*<<< orphan*/  FLAGS_OUTPUT_READY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t omap_sham_irq_common(struct omap_sham_dev *dd)
{
	if (!test_bit(FLAGS_BUSY, &dd->flags)) {
		dev_warn(dd->dev, "Interrupt when no active requests.\n");
	} else {
		set_bit(FLAGS_OUTPUT_READY, &dd->flags);
		tasklet_schedule(&dd->done_task);
	}

	return IRQ_HANDLED;
}