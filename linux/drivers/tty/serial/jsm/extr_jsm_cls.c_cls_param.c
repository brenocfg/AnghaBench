#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_9__ {TYPE_2__* state; } ;
struct jsm_channel {int ch_c_cflag; int ch_flags; int ch_mostat; int ch_c_iflag; scalar_t__ ch_startc; scalar_t__ ch_stopc; TYPE_4__* ch_cls_uart; struct jsm_board* ch_bd; TYPE_3__ uart_port; scalar_t__ ch_e_tail; scalar_t__ ch_e_head; scalar_t__ ch_r_tail; scalar_t__ ch_r_head; } ;
struct jsm_board {int bd_dividend; } ;
struct TYPE_11__ {unsigned int cflag; int rate; } ;
struct TYPE_10__ {int /*<<< orphan*/  msr; int /*<<< orphan*/  ier; int /*<<< orphan*/  lcr; int /*<<< orphan*/  txrx; } ;
struct TYPE_7__ {int /*<<< orphan*/  tty; } ;
struct TYPE_8__ {TYPE_1__ port; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
 int CBAUD ; 
 int CH_BAUD0 ; 
 int CMSPAR ; 
 int CREAD ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 unsigned int C_BAUD (int /*<<< orphan*/ ) ; 
 int IXOFF ; 
 int IXON ; 
 int PARENB ; 
 int PARODD ; 
 int UART_IER_MSI ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int UART_IER_THRI ; 
 int UART_LCR_DLAB ; 
 int UART_LCR_EPAR ; 
 int UART_LCR_PARITY ; 
 int UART_LCR_SPAR ; 
 int UART_LCR_STOP ; 
 int UART_LCR_WLEN5 ; 
 int UART_LCR_WLEN6 ; 
 int UART_LCR_WLEN7 ; 
 int UART_LCR_WLEN8 ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 scalar_t__ __DISABLED_CHAR ; 
 TYPE_5__* baud_rates ; 
 int /*<<< orphan*/  cls_assert_modem_signals (struct jsm_channel*) ; 
 int /*<<< orphan*/  cls_flush_uart_read (struct jsm_channel*) ; 
 int /*<<< orphan*/  cls_flush_uart_write (struct jsm_channel*) ; 
 int /*<<< orphan*/  cls_parse_modem (struct jsm_channel*,int) ; 
 int /*<<< orphan*/  cls_set_cts_flow_control (struct jsm_channel*) ; 
 int /*<<< orphan*/  cls_set_ixoff_flow_control (struct jsm_channel*) ; 
 int /*<<< orphan*/  cls_set_ixon_flow_control (struct jsm_channel*) ; 
 int /*<<< orphan*/  cls_set_no_input_flow_control (struct jsm_channel*) ; 
 int /*<<< orphan*/  cls_set_no_output_flow_control (struct jsm_channel*) ; 
 int /*<<< orphan*/  cls_set_rts_flow_control (struct jsm_channel*) ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cls_param(struct jsm_channel *ch)
{
	u8 lcr = 0;
	u8 uart_lcr = 0;
	u8 ier = 0;
	u32 baud = 9600;
	int quot = 0;
	struct jsm_board *bd;
	int i;
	unsigned int cflag;

	bd = ch->ch_bd;
	if (!bd)
		return;

	/*
	 * If baud rate is zero, flush queues, and set mval to drop DTR.
	 */
	if ((ch->ch_c_cflag & (CBAUD)) == 0) {
		ch->ch_r_head = 0;
		ch->ch_r_tail = 0;
		ch->ch_e_head = 0;
		ch->ch_e_tail = 0;

		cls_flush_uart_write(ch);
		cls_flush_uart_read(ch);

		/* The baudrate is B0 so all modem lines are to be dropped. */
		ch->ch_flags |= (CH_BAUD0);
		ch->ch_mostat &= ~(UART_MCR_RTS | UART_MCR_DTR);
		cls_assert_modem_signals(ch);
		return;
	}

	cflag = C_BAUD(ch->uart_port.state->port.tty);
	baud = 9600;
	for (i = 0; i < ARRAY_SIZE(baud_rates); i++) {
		if (baud_rates[i].cflag == cflag) {
			baud = baud_rates[i].rate;
			break;
		}
	}

	if (ch->ch_flags & CH_BAUD0)
		ch->ch_flags &= ~(CH_BAUD0);

	if (ch->ch_c_cflag & PARENB)
		lcr |= UART_LCR_PARITY;

	if (!(ch->ch_c_cflag & PARODD))
		lcr |= UART_LCR_EPAR;

	/*
	 * Not all platforms support mark/space parity,
	 * so this will hide behind an ifdef.
	 */
#ifdef CMSPAR
	if (ch->ch_c_cflag & CMSPAR)
		lcr |= UART_LCR_SPAR;
#endif

	if (ch->ch_c_cflag & CSTOPB)
		lcr |= UART_LCR_STOP;

	switch (ch->ch_c_cflag & CSIZE) {
	case CS5:
		lcr |= UART_LCR_WLEN5;
		break;
	case CS6:
		lcr |= UART_LCR_WLEN6;
		break;
	case CS7:
		lcr |= UART_LCR_WLEN7;
		break;
	case CS8:
	default:
		lcr |= UART_LCR_WLEN8;
		break;
	}

	ier = readb(&ch->ch_cls_uart->ier);
	uart_lcr = readb(&ch->ch_cls_uart->lcr);

	quot = ch->ch_bd->bd_dividend / baud;

	if (quot != 0) {
		writeb(UART_LCR_DLAB, &ch->ch_cls_uart->lcr);
		writeb((quot & 0xff), &ch->ch_cls_uart->txrx);
		writeb((quot >> 8), &ch->ch_cls_uart->ier);
		writeb(lcr, &ch->ch_cls_uart->lcr);
	}

	if (uart_lcr != lcr)
		writeb(lcr, &ch->ch_cls_uart->lcr);

	if (ch->ch_c_cflag & CREAD)
		ier |= (UART_IER_RDI | UART_IER_RLSI);

	ier |= (UART_IER_THRI | UART_IER_MSI);

	writeb(ier, &ch->ch_cls_uart->ier);

	if (ch->ch_c_cflag & CRTSCTS)
		cls_set_cts_flow_control(ch);
	else if (ch->ch_c_iflag & IXON) {
		/*
		 * If start/stop is set to disable,
		 * then we should disable flow control.
		 */
		if ((ch->ch_startc == __DISABLED_CHAR) ||
			(ch->ch_stopc == __DISABLED_CHAR))
			cls_set_no_output_flow_control(ch);
		else
			cls_set_ixon_flow_control(ch);
	} else
		cls_set_no_output_flow_control(ch);

	if (ch->ch_c_cflag & CRTSCTS)
		cls_set_rts_flow_control(ch);
	else if (ch->ch_c_iflag & IXOFF) {
		/*
		 * If start/stop is set to disable,
		 * then we should disable flow control.
		 */
		if ((ch->ch_startc == __DISABLED_CHAR) ||
			(ch->ch_stopc == __DISABLED_CHAR))
			cls_set_no_input_flow_control(ch);
		else
			cls_set_ixoff_flow_control(ch);
	} else
		cls_set_no_input_flow_control(ch);

	cls_assert_modem_signals(ch);

	/* get current status of the modem signals now */
	cls_parse_modem(ch, readb(&ch->ch_cls_uart->msr));
}