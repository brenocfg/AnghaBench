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
typedef  int u8 ;
struct jsm_channel {int ch_flags; TYPE_1__* ch_cls_uart; } ;
struct TYPE_2__ {int /*<<< orphan*/  lcr; } ;

/* Variables and functions */
 int CH_BREAK_SENDING ; 
 int UART_LCR_SBC ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cls_send_break(struct jsm_channel *ch)
{
	/* Tell the UART to start sending the break */
	if (!(ch->ch_flags & CH_BREAK_SENDING)) {
		u8 temp = readb(&ch->ch_cls_uart->lcr);

		writeb((temp | UART_LCR_SBC), &ch->ch_cls_uart->lcr);
		ch->ch_flags |= (CH_BREAK_SENDING);
	}
}