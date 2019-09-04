#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* mdmreg; } ;
struct TYPE_9__ {int /*<<< orphan*/  tty; } ;
struct TYPE_11__ {int isdn_driver; int isdn_channel; int last_lhup; int msr; size_t drv_index; TYPE_2__ emu; int /*<<< orphan*/  lsr; scalar_t__ online; TYPE_1__ port; scalar_t__ rcvsched; } ;
typedef  TYPE_3__ modem_info ;
struct TYPE_12__ {int driver; int arg; int /*<<< orphan*/  command; } ;
typedef  TYPE_4__ isdn_ctrl ;
struct TYPE_13__ {int* m_idx; } ;

/* Variables and functions */
 int BIT_RUNG ; 
 int /*<<< orphan*/  ISDN_CMD_HANGUP ; 
 size_t REG_RINGCNT ; 
 size_t REG_RUNG ; 
 int /*<<< orphan*/  RESULT_NO_CARRIER ; 
 int /*<<< orphan*/  RESULT_RUNG ; 
 int /*<<< orphan*/  UART_LSR_TEMT ; 
 int UART_MSR_DCD ; 
 int UART_MSR_RI ; 
 TYPE_8__* dev ; 
 int /*<<< orphan*/  isdn_all_eaz (int,int) ; 
 int /*<<< orphan*/  isdn_command (TYPE_4__*) ; 
 int /*<<< orphan*/  isdn_free_channel (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdn_tty_flush_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdn_tty_modem_result (int /*<<< orphan*/ ,TYPE_3__*) ; 

void
isdn_tty_modem_hup(modem_info *info, int local)
{
	isdn_ctrl cmd;
	int di, ch;

	if (!info)
		return;

	di = info->isdn_driver;
	ch = info->isdn_channel;
	if (di < 0 || ch < 0)
		return;

	info->isdn_driver = -1;
	info->isdn_channel = -1;

#ifdef ISDN_DEBUG_MODEM_HUP
	printk(KERN_DEBUG "Mhup ttyI%d\n", info->line);
#endif
	info->rcvsched = 0;
	isdn_tty_flush_buffer(info->port.tty);
	if (info->online) {
		info->last_lhup = local;
		info->online = 0;
		isdn_tty_modem_result(RESULT_NO_CARRIER, info);
	}
#ifdef CONFIG_ISDN_AUDIO
	info->vonline = 0;
#ifdef CONFIG_ISDN_TTY_FAX
	info->faxonline = 0;
	info->fax->phase = ISDN_FAX_PHASE_IDLE;
#endif
	info->emu.vpar[4] = 0;
	info->emu.vpar[5] = 8;
	kfree(info->dtmf_state);
	info->dtmf_state = NULL;
	kfree(info->silence_state);
	info->silence_state = NULL;
	kfree(info->adpcms);
	info->adpcms = NULL;
	kfree(info->adpcmr);
	info->adpcmr = NULL;
#endif
	if ((info->msr & UART_MSR_RI) &&
	    (info->emu.mdmreg[REG_RUNG] & BIT_RUNG))
		isdn_tty_modem_result(RESULT_RUNG, info);
	info->msr &= ~(UART_MSR_DCD | UART_MSR_RI);
	info->lsr |= UART_LSR_TEMT;

	if (local) {
		cmd.driver = di;
		cmd.command = ISDN_CMD_HANGUP;
		cmd.arg = ch;
		isdn_command(&cmd);
	}

	isdn_all_eaz(di, ch);
	info->emu.mdmreg[REG_RINGCNT] = 0;
	isdn_free_channel(di, ch, 0);

	if (info->drv_index >= 0) {
		dev->m_idx[info->drv_index] = -1;
		info->drv_index = -1;
	}
}