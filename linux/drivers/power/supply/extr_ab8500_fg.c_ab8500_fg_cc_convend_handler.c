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
struct ab8500_fg {int /*<<< orphan*/  fg_acc_cur_work; int /*<<< orphan*/  fg_wq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ab8500_fg_cc_convend_handler(int irq, void *_di)
{
	struct ab8500_fg *di = _di;

	queue_work(di->fg_wq, &di->fg_acc_cur_work);

	return IRQ_HANDLED;
}