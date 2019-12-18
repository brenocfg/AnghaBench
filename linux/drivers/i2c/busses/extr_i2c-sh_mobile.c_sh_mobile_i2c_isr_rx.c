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
struct sh_mobile_i2c_data {int pos; TYPE_1__* msg; scalar_t__ stop_after_dma; } ;
struct TYPE_2__ {int len; unsigned char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_RX ; 
 int /*<<< orphan*/  OP_RX_STOP ; 
 int /*<<< orphan*/  OP_RX_STOP_DATA ; 
 int /*<<< orphan*/  OP_TX_FIRST ; 
 int /*<<< orphan*/  OP_TX_TO_RX ; 
 unsigned char i2c_op (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mobile_i2c_isr_rx(struct sh_mobile_i2c_data *pd)
{
	unsigned char data;
	int real_pos;

	/* switch from TX (address) to RX (data) adds two interrupts */
	real_pos = pd->pos - 2;

	if (pd->pos == -1) {
		i2c_op(pd, OP_TX_FIRST);
	} else if (pd->pos == 0) {
		i2c_op(pd, OP_TX_TO_RX);
	} else if (pd->pos == pd->msg->len) {
		if (pd->stop_after_dma) {
			/* Simulate PIO end condition after DMA transfer */
			i2c_op(pd, OP_RX_STOP);
			pd->pos++;
			goto done;
		}

		if (real_pos < 0)
			i2c_op(pd, OP_RX_STOP);
		else
			data = i2c_op(pd, OP_RX_STOP_DATA);
	} else if (real_pos >= 0) {
		data = i2c_op(pd, OP_RX);
	}

	if (real_pos >= 0)
		pd->msg->buf[real_pos] = data;
 done:
	pd->pos++;
	return pd->pos == (pd->msg->len + 2);
}