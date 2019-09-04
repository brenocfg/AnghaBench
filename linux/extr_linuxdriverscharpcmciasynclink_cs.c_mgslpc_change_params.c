#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int c_cflag; } ;
struct tty_struct {TYPE_1__ termios; } ;
struct TYPE_7__ {int data_bits; int stop_bits; int data_rate; int /*<<< orphan*/  parity; } ;
struct TYPE_8__ {int serial_signals; int timeout; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  port; TYPE_2__ params; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_3__ MGSLPC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_PARITY_EVEN ; 
 int /*<<< orphan*/  ASYNC_PARITY_NONE ; 
 int /*<<< orphan*/  ASYNC_PARITY_ODD ; 
 int BIT6 ; 
 int BIT7 ; 
 unsigned int CBAUD ; 
 unsigned int CLOCAL ; 
 unsigned int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int HZ ; 
 scalar_t__ I_IGNPAR (struct tty_struct*) ; 
 scalar_t__ I_INPCK (struct tty_struct*) ; 
 unsigned int PARENB ; 
 unsigned int PARODD ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  mgslpc_program_hw (TYPE_3__*,struct tty_struct*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int tty_get_baud_rate (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_set_check_carrier (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  tty_port_set_cts_flow (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void mgslpc_change_params(MGSLPC_INFO *info, struct tty_struct *tty)
{
	unsigned cflag;
	int bits_per_char;

	if (!tty)
		return;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_change_params(%s)\n",
			 __FILE__, __LINE__, info->device_name);

	cflag = tty->termios.c_cflag;

	/* if B0 rate (hangup) specified then negate RTS and DTR */
	/* otherwise assert RTS and DTR */
	if (cflag & CBAUD)
		info->serial_signals |= SerialSignal_RTS | SerialSignal_DTR;
	else
		info->serial_signals &= ~(SerialSignal_RTS | SerialSignal_DTR);

	/* byte size and parity */

	switch (cflag & CSIZE) {
	case CS5: info->params.data_bits = 5; break;
	case CS6: info->params.data_bits = 6; break;
	case CS7: info->params.data_bits = 7; break;
	case CS8: info->params.data_bits = 8; break;
	default:  info->params.data_bits = 7; break;
	}

	if (cflag & CSTOPB)
		info->params.stop_bits = 2;
	else
		info->params.stop_bits = 1;

	info->params.parity = ASYNC_PARITY_NONE;
	if (cflag & PARENB) {
		if (cflag & PARODD)
			info->params.parity = ASYNC_PARITY_ODD;
		else
			info->params.parity = ASYNC_PARITY_EVEN;
#ifdef CMSPAR
		if (cflag & CMSPAR)
			info->params.parity = ASYNC_PARITY_SPACE;
#endif
	}

	/* calculate number of jiffies to transmit a full
	 * FIFO (32 bytes) at specified data rate
	 */
	bits_per_char = info->params.data_bits +
			info->params.stop_bits + 1;

	/* if port data rate is set to 460800 or less then
	 * allow tty settings to override, otherwise keep the
	 * current data rate.
	 */
	if (info->params.data_rate <= 460800) {
		info->params.data_rate = tty_get_baud_rate(tty);
	}

	if (info->params.data_rate) {
		info->timeout = (32*HZ*bits_per_char) /
				info->params.data_rate;
	}
	info->timeout += HZ/50;		/* Add .02 seconds of slop */

	tty_port_set_cts_flow(&info->port, cflag & CRTSCTS);
	tty_port_set_check_carrier(&info->port, ~cflag & CLOCAL);

	/* process tty input control flags */

	info->read_status_mask = 0;
	if (I_INPCK(tty))
		info->read_status_mask |= BIT7 | BIT6;
	if (I_IGNPAR(tty))
		info->ignore_status_mask |= BIT7 | BIT6;

	mgslpc_program_hw(info, tty);
}