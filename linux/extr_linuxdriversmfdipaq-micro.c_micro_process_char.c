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
struct ipaq_micro_rxdev {int state; int id; int len; size_t index; int chksum; int* buf; } ;
struct ipaq_micro {struct ipaq_micro_rxdev rx; } ;

/* Variables and functions */
 int CHAR_SOF ; 
#define  STATE_CHKSUM 131 
#define  STATE_DATA 130 
#define  STATE_ID 129 
#define  STATE_SOF 128 
 int /*<<< orphan*/  micro_rx_msg (struct ipaq_micro*,int,size_t,int*) ; 

__attribute__((used)) static void micro_process_char(struct ipaq_micro *micro, u8 ch)
{
	struct ipaq_micro_rxdev *rx = &micro->rx;

	switch (rx->state) {
	case STATE_SOF:	/* Looking for SOF */
		if (ch == CHAR_SOF)
			rx->state = STATE_ID; /* Next byte is the id and len */
		break;
	case STATE_ID: /* Looking for id and len byte */
		rx->id = (ch & 0xf0) >> 4;
		rx->len = (ch & 0x0f);
		rx->index = 0;
		rx->chksum = ch;
		rx->state = (rx->len > 0) ? STATE_DATA : STATE_CHKSUM;
		break;
	case STATE_DATA: /* Looking for 'len' data bytes */
		rx->chksum += ch;
		rx->buf[rx->index] = ch;
		if (++rx->index == rx->len)
			rx->state = STATE_CHKSUM;
		break;
	case STATE_CHKSUM: /* Looking for the checksum */
		if (ch == rx->chksum)
			micro_rx_msg(micro, rx->id, rx->len, rx->buf);
		rx->state = STATE_SOF;
		break;
	}
}