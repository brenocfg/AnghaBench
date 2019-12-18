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
struct amvdec_core {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PARSER_INTSTAT_SC_FOUND ; 
 int /*<<< orphan*/  PARSER_INT_STATUS ; 
 int /*<<< orphan*/  PFIFO_RD_PTR ; 
 int /*<<< orphan*/  PFIFO_WR_PTR ; 
 int amvdec_read_parser (struct amvdec_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amvdec_write_parser (struct amvdec_core*,int /*<<< orphan*/ ,int) ; 
 int search_done ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static irqreturn_t esparser_isr(int irq, void *dev)
{
	int int_status;
	struct amvdec_core *core = dev;

	int_status = amvdec_read_parser(core, PARSER_INT_STATUS);
	amvdec_write_parser(core, PARSER_INT_STATUS, int_status);

	if (int_status & PARSER_INTSTAT_SC_FOUND) {
		amvdec_write_parser(core, PFIFO_RD_PTR, 0);
		amvdec_write_parser(core, PFIFO_WR_PTR, 0);
		search_done = 1;
		wake_up_interruptible(&wq);
	}

	return IRQ_HANDLED;
}