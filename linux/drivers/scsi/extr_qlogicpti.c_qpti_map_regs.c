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
struct qlogicpti {void* sreg; scalar_t__ is_pti; void* qregs; struct platform_device* op; } ;
struct platform_device {int /*<<< orphan*/ * resource; } ;

/* Variables and functions */
 int ENODEV ; 
 void* of_ioremap (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int resource_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qpti_map_regs(struct qlogicpti *qpti)
{
	struct platform_device *op = qpti->op;

	qpti->qregs = of_ioremap(&op->resource[0], 0,
				 resource_size(&op->resource[0]),
				 "PTI Qlogic/ISP");
	if (!qpti->qregs) {
		printk("PTI: Qlogic/ISP registers are unmappable\n");
		return -ENODEV;
	}
	if (qpti->is_pti) {
		qpti->sreg = of_ioremap(&op->resource[0], (16 * 4096),
					sizeof(unsigned char),
					"PTI Qlogic/ISP statreg");
		if (!qpti->sreg) {
			printk("PTI: Qlogic/ISP status register is unmappable\n");
			return -ENODEV;
		}
	}
	return 0;
}