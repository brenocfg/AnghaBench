#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* mdmreg; } ;
struct TYPE_7__ {int mcr; int rcvsched; int /*<<< orphan*/  port; int /*<<< orphan*/  isdn_channel; int /*<<< orphan*/  isdn_driver; TYPE_2__ emu; int /*<<< orphan*/  online; } ;
typedef  TYPE_3__ modem_info ;
struct TYPE_5__ {TYPE_3__* info; } ;
struct TYPE_8__ {int* m_idx; TYPE_1__ mdm; } ;

/* Variables and functions */
 int BIT_CPPP ; 
 int ISDN_MAX_CHANNELS ; 
 int /*<<< orphan*/  ISDN_TIMER_MODEMREAD ; 
 size_t REG_CPPP ; 
 int UART_MCR_RTS ; 
 TYPE_4__* dev ; 
 int isdn_readbchan_tty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isdn_timer_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 

void
isdn_tty_readmodem(void)
{
	int resched = 0;
	int midx;
	int i;
	int r;
	modem_info *info;

	for (i = 0; i < ISDN_MAX_CHANNELS; i++) {
		midx = dev->m_idx[i];
		if (midx < 0)
			continue;

		info = &dev->mdm.info[midx];
		if (!info->online)
			continue;

		r = 0;
#ifdef CONFIG_ISDN_AUDIO
		isdn_audio_eval_dtmf(info);
		if ((info->vonline & 1) && (info->emu.vpar[1]))
			isdn_audio_eval_silence(info);
#endif
		if (info->mcr & UART_MCR_RTS) {
			/* CISCO AsyncPPP Hack */
			if (!(info->emu.mdmreg[REG_CPPP] & BIT_CPPP))
				r = isdn_readbchan_tty(info->isdn_driver,
						info->isdn_channel,
						&info->port, 0);
			else
				r = isdn_readbchan_tty(info->isdn_driver,
						info->isdn_channel,
						&info->port, 1);
			if (r)
				tty_flip_buffer_push(&info->port);
		} else
			r = 1;

		if (r) {
			info->rcvsched = 0;
			resched = 1;
		} else
			info->rcvsched = 1;
	}
	if (!resched)
		isdn_timer_ctrl(ISDN_TIMER_MODEMREAD, 0);
}