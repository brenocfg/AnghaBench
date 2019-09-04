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
typedef  int u8 ;
struct ams_delta_serio {int* fiq_buffer; int /*<<< orphan*/  serio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t FIQ_BUF_LEN ; 
 size_t FIQ_CIRC_BUFF ; 
 size_t FIQ_HEAD_OFFSET ; 
 size_t FIQ_IRQ_PEND ; 
 size_t FIQ_KEYS_CNT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int check_data (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serio_interrupt (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t ams_delta_serio_interrupt(int irq, void *dev_id)
{
	struct ams_delta_serio *priv = dev_id;
	int *circ_buff = &priv->fiq_buffer[FIQ_CIRC_BUFF];
	int data, dfl;
	u8 scancode;

	priv->fiq_buffer[FIQ_IRQ_PEND] = 0;

	/*
	 * Read data from the circular buffer, check it
	 * and then pass it on the serio
	 */
	while (priv->fiq_buffer[FIQ_KEYS_CNT] > 0) {

		data = circ_buff[priv->fiq_buffer[FIQ_HEAD_OFFSET]++];
		priv->fiq_buffer[FIQ_KEYS_CNT]--;
		if (priv->fiq_buffer[FIQ_HEAD_OFFSET] ==
		    priv->fiq_buffer[FIQ_BUF_LEN])
			priv->fiq_buffer[FIQ_HEAD_OFFSET] = 0;

		dfl = check_data(priv->serio, data);
		scancode = (u8) (data >> 1) & 0xFF;
		serio_interrupt(priv->serio, scancode, dfl);
	}
	return IRQ_HANDLED;
}