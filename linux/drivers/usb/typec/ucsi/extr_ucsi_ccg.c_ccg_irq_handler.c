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
struct ucsi_ccg {int /*<<< orphan*/  ucsi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ucsi_notify (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ccg_irq_handler(int irq, void *data)
{
	struct ucsi_ccg *uc = data;

	ucsi_notify(uc->ucsi);

	return IRQ_HANDLED;
}