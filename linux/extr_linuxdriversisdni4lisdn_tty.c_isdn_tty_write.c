#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct tty_struct {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct TYPE_14__ {int /*<<< orphan*/ * xmit_buf; } ;
struct TYPE_16__ {int* mdmreg; int /*<<< orphan*/  lastplus; int /*<<< orphan*/  pluscount; } ;
struct TYPE_15__ {int xmit_size; size_t xmit_count; size_t isdn_driver; int online; int /*<<< orphan*/  xmit_queue; int /*<<< orphan*/  xmit_lock; scalar_t__ dialing; int /*<<< orphan*/  lsr; int /*<<< orphan*/  msr; TYPE_2__ port; TYPE_4__ emu; } ;
typedef  TYPE_3__ modem_info ;
typedef  TYPE_4__ atemu ;
struct TYPE_13__ {int maxbufsize; } ;
struct TYPE_12__ {TYPE_1__** drv; } ;

/* Variables and functions */
 int BIT_DXMT ; 
 int /*<<< orphan*/  ISDN_TIMER_MODEMXMIT ; 
 size_t REG_DXMT ; 
 size_t REG_ESC ; 
 int /*<<< orphan*/  RESULT_NO_CARRIER ; 
 int /*<<< orphan*/  UART_LSR_TEMT ; 
 int /*<<< orphan*/  UART_MSR_CTS ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_11__* dev ; 
 int /*<<< orphan*/  isdn_timer_ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isdn_tty_check_esc (int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int isdn_tty_edit_at (int /*<<< orphan*/  const*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  isdn_tty_modem_hup (TYPE_3__*,int) ; 
 int /*<<< orphan*/  isdn_tty_modem_result (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ isdn_tty_paranoia_check (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isdn_tty_senddown (TYPE_3__*) ; 
 int /*<<< orphan*/  isdn_tty_tint (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isdn_tty_write(struct tty_struct *tty, const u_char *buf, int count)
{
	int c;
	int total = 0;
	modem_info *info = (modem_info *) tty->driver_data;
	atemu *m = &info->emu;

	if (isdn_tty_paranoia_check(info, tty->name, "isdn_tty_write"))
		return 0;
	/* See isdn_tty_senddown() */
	atomic_inc(&info->xmit_lock);
	while (1) {
		c = count;
		if (c > info->xmit_size - info->xmit_count)
			c = info->xmit_size - info->xmit_count;
		if (info->isdn_driver >= 0 && c > dev->drv[info->isdn_driver]->maxbufsize)
			c = dev->drv[info->isdn_driver]->maxbufsize;
		if (c <= 0)
			break;
		if ((info->online > 1)
#ifdef CONFIG_ISDN_AUDIO
		    || (info->vonline & 3)
#endif
			) {
#ifdef CONFIG_ISDN_AUDIO
			if (!info->vonline)
#endif
				isdn_tty_check_esc(buf, m->mdmreg[REG_ESC], c,
						   &(m->pluscount),
						   &(m->lastplus));
			memcpy(&info->port.xmit_buf[info->xmit_count], buf, c);
#ifdef CONFIG_ISDN_AUDIO
			if (info->vonline) {
				int cc = isdn_tty_handleDLEdown(info, m, c);
				if (info->vonline & 2) {
					if (!cc) {
						/* If DLE decoding results in zero-transmit, but
						 * c originally was non-zero, do a wakeup.
						 */
						tty_wakeup(tty);
						info->msr |= UART_MSR_CTS;
						info->lsr |= UART_LSR_TEMT;
					}
					info->xmit_count += cc;
				}
				if ((info->vonline & 3) == 1) {
					/* Do NOT handle Ctrl-Q or Ctrl-S
					 * when in full-duplex audio mode.
					 */
					if (isdn_tty_end_vrx(buf, c)) {
						info->vonline &= ~1;
#ifdef ISDN_DEBUG_MODEM_VOICE
						printk(KERN_DEBUG
						       "got !^Q/^S, send DLE-ETX,VCON on ttyI%d\n",
						       info->line);
#endif
						isdn_tty_at_cout("\020\003\r\nVCON\r\n", info);
					}
				}
			} else
				if (TTY_IS_FCLASS1(info)) {
					int cc = isdn_tty_handleDLEdown(info, m, c);

					if (info->vonline & 4) { /* ETX seen */
						isdn_ctrl c;

						c.command = ISDN_CMD_FAXCMD;
						c.driver = info->isdn_driver;
						c.arg = info->isdn_channel;
						c.parm.aux.cmd = ISDN_FAX_CLASS1_CTRL;
						c.parm.aux.subcmd = ETX;
						isdn_command(&c);
					}
					info->vonline = 0;
#ifdef ISDN_DEBUG_MODEM_VOICE
					printk(KERN_DEBUG "fax dle cc/c %d/%d\n", cc, c);
#endif
					info->xmit_count += cc;
				} else
#endif
					info->xmit_count += c;
		} else {
			info->msr |= UART_MSR_CTS;
			info->lsr |= UART_LSR_TEMT;
			if (info->dialing) {
				info->dialing = 0;
#ifdef ISDN_DEBUG_MODEM_HUP
				printk(KERN_DEBUG "Mhup in isdn_tty_write\n");
#endif
				isdn_tty_modem_result(RESULT_NO_CARRIER, info);
				isdn_tty_modem_hup(info, 1);
			} else
				c = isdn_tty_edit_at(buf, c, info);
		}
		buf += c;
		count -= c;
		total += c;
	}
	atomic_dec(&info->xmit_lock);
	if ((info->xmit_count) || !skb_queue_empty(&info->xmit_queue)) {
		if (m->mdmreg[REG_DXMT] & BIT_DXMT) {
			isdn_tty_senddown(info);
			isdn_tty_tint(info);
		}
		isdn_timer_ctrl(ISDN_TIMER_MODEMXMIT, 1);
	}
	return total;
}