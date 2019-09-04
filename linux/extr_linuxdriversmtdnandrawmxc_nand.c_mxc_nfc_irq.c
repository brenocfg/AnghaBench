#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mxc_nand_host {int /*<<< orphan*/  op_completion; TYPE_1__* devtype_data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* check_int ) (struct mxc_nand_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_control (struct mxc_nand_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mxc_nand_host*) ; 

__attribute__((used)) static irqreturn_t mxc_nfc_irq(int irq, void *dev_id)
{
	struct mxc_nand_host *host = dev_id;

	if (!host->devtype_data->check_int(host))
		return IRQ_NONE;

	irq_control(host, 0);

	complete(&host->op_completion);

	return IRQ_HANDLED;
}