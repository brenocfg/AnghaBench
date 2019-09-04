#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* mdmreg; scalar_t__ carrierwait; } ;
struct TYPE_8__ {int msr; size_t drv_index; int last_l2; int dialing; TYPE_3__ emu; scalar_t__ isdn_channel; int /*<<< orphan*/  isdn_driver; int /*<<< orphan*/  last_num; scalar_t__ last_dir; } ;
typedef  TYPE_1__ modem_info ;
struct TYPE_9__ {int /*<<< orphan*/  command; scalar_t__ arg; int /*<<< orphan*/  driver; } ;
typedef  TYPE_2__ isdn_ctrl ;
typedef  TYPE_3__ atemu ;
struct TYPE_11__ {int /*<<< orphan*/ * num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_CMD_ACCEPTD ; 
 int /*<<< orphan*/  ISDN_CMD_SETL2 ; 
 int /*<<< orphan*/  ISDN_CMD_SETL3 ; 
 int /*<<< orphan*/  ISDN_TIMER_CARRIER ; 
 size_t REG_L2PROT ; 
 size_t REG_L3PROT ; 
 size_t REG_RINGCNT ; 
 int /*<<< orphan*/  RESULT_NO_ANSWER ; 
 int UART_MSR_RI ; 
 TYPE_7__* dev ; 
 int /*<<< orphan*/  isdn_command (TYPE_2__*) ; 
 int /*<<< orphan*/  isdn_timer_ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isdn_tty_modem_result (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isdn_tty_cmd_ATA(modem_info *info)
{
	atemu *m = &info->emu;
	isdn_ctrl cmd;
	int l2;

	if (info->msr & UART_MSR_RI) {
		/* Accept incoming call */
		info->last_dir = 0;
		strcpy(info->last_num, dev->num[info->drv_index]);
		m->mdmreg[REG_RINGCNT] = 0;
		info->msr &= ~UART_MSR_RI;
		l2 = m->mdmreg[REG_L2PROT];
#ifdef CONFIG_ISDN_AUDIO
		/* If more than one bit set in reg18, autoselect Layer2 */
		if ((m->mdmreg[REG_SI1] & m->mdmreg[REG_SI1I]) != m->mdmreg[REG_SI1]) {
			if (m->mdmreg[REG_SI1I] == 1) {
				if ((l2 != ISDN_PROTO_L2_MODEM) && (l2 != ISDN_PROTO_L2_FAX))
					l2 = ISDN_PROTO_L2_TRANS;
			} else
				l2 = ISDN_PROTO_L2_X75I;
		}
#endif
		cmd.driver = info->isdn_driver;
		cmd.command = ISDN_CMD_SETL2;
		cmd.arg = info->isdn_channel + (l2 << 8);
		info->last_l2 = l2;
		isdn_command(&cmd);
		cmd.driver = info->isdn_driver;
		cmd.command = ISDN_CMD_SETL3;
		cmd.arg = info->isdn_channel + (m->mdmreg[REG_L3PROT] << 8);
#ifdef CONFIG_ISDN_TTY_FAX
		if (l2 == ISDN_PROTO_L2_FAX) {
			cmd.parm.fax = info->fax;
			info->fax->direction = ISDN_TTY_FAX_CONN_IN;
		}
#endif
		isdn_command(&cmd);
		cmd.driver = info->isdn_driver;
		cmd.arg = info->isdn_channel;
		cmd.command = ISDN_CMD_ACCEPTD;
		info->dialing = 16;
		info->emu.carrierwait = 0;
		isdn_command(&cmd);
		isdn_timer_ctrl(ISDN_TIMER_CARRIER, 1);
	} else
		isdn_tty_modem_result(RESULT_NO_ANSWER, info);
}