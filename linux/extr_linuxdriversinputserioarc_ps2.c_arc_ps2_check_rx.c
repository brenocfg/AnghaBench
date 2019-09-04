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
struct arc_ps2_port {TYPE_1__* io; int /*<<< orphan*/  data_addr; int /*<<< orphan*/  status_addr; } ;
struct arc_ps2_data {int /*<<< orphan*/  buf_overflow; int /*<<< orphan*/  frame_error; int /*<<< orphan*/  total_int; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int PS2_STAT_RX_BUF_OVER ; 
 unsigned int PS2_STAT_RX_FRM_ERR ; 
 unsigned int PS2_STAT_RX_VAL ; 
 unsigned int SERIO_FRAME ; 
 unsigned int SERIO_PARITY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_interrupt (TYPE_1__*,unsigned char,unsigned int) ; 

__attribute__((used)) static void arc_ps2_check_rx(struct arc_ps2_data *arc_ps2,
			     struct arc_ps2_port *port)
{
	unsigned int timeout = 1000;
	unsigned int flag, status;
	unsigned char data;

	do {
		status = ioread32(port->status_addr);
		if (!(status & PS2_STAT_RX_VAL))
			return;

		data = ioread32(port->data_addr) & 0xff;

		flag = 0;
		arc_ps2->total_int++;
		if (status & PS2_STAT_RX_FRM_ERR) {
			arc_ps2->frame_error++;
			flag |= SERIO_PARITY;
		} else if (status & PS2_STAT_RX_BUF_OVER) {
			arc_ps2->buf_overflow++;
			flag |= SERIO_FRAME;
		}

		serio_interrupt(port->io, data, flag);
	} while (--timeout);

	dev_err(&port->io->dev, "PS/2 hardware stuck\n");
}