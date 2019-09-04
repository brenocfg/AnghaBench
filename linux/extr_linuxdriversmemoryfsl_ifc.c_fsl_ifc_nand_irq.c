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
struct fsl_ifc_ctrl {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ check_nand_stat (struct fsl_ifc_ctrl*) ; 

__attribute__((used)) static irqreturn_t fsl_ifc_nand_irq(int irqno, void *data)
{
	struct fsl_ifc_ctrl *ctrl = data;

	if (check_nand_stat(ctrl))
		return IRQ_HANDLED;

	return IRQ_NONE;
}