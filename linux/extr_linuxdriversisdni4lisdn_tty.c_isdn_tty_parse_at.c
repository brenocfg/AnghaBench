#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {char* mdmcmd; char* msn; int charge; int /*<<< orphan*/ * mdmreg; } ;
struct TYPE_20__ {int msr; int /*<<< orphan*/  online; TYPE_2__ emu; } ;
typedef  TYPE_1__ modem_info ;
typedef  int /*<<< orphan*/  ds ;
typedef  TYPE_2__ atemu ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ECHO ; 
 int /*<<< orphan*/  BIT_RESP ; 
 int /*<<< orphan*/  BIT_RESPNUM ; 
 int ISDN_MSNLEN ; 
 int /*<<< orphan*/  ISDN_PROTO_L2_MODEM ; 
 int /*<<< orphan*/  PARSE_ERROR ; 
 size_t REG_ECHO ; 
 size_t REG_L2PROT ; 
 size_t REG_RESP ; 
 int /*<<< orphan*/  RESULT_CONNECT ; 
 int /*<<< orphan*/  RESULT_CONNECT64000 ; 
 int /*<<< orphan*/  RESULT_NO_CARRIER ; 
 int /*<<< orphan*/  RESULT_NO_MSN_EAZ ; 
 int /*<<< orphan*/  RESULT_OK ; 
 int UART_MSR_DCD ; 
 int UART_MSR_RI ; 
 int /*<<< orphan*/  isdn_getnum (char**) ; 
 int /*<<< orphan*/  isdn_tty_at_cout (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_tty_cmd_ATA (TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_tty_cmd_ATS (char**,TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_tty_cmd_ATand (char**,TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_tty_dial (char*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  isdn_tty_get_msnstr (char*,char**) ; 
 int /*<<< orphan*/  isdn_tty_getdial (char*,char*,int) ; 
 int /*<<< orphan*/  isdn_tty_modem_reset_regs (TYPE_1__*,int) ; 
 int /*<<< orphan*/  isdn_tty_modem_result (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_tty_off_hook () ; 
 int /*<<< orphan*/  isdn_tty_on_hook (TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_tty_report (TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_tty_resume (char*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  isdn_tty_send_msg (TYPE_1__*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  isdn_tty_suspend (char*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
isdn_tty_parse_at(modem_info *info)
{
	atemu *m = &info->emu;
	char *p;
	char ds[ISDN_MSNLEN];

#ifdef ISDN_DEBUG_AT
	printk(KERN_DEBUG "AT: '%s'\n", m->mdmcmd);
#endif
	for (p = &m->mdmcmd[2]; *p;) {
		switch (*p) {
		case ' ':
			p++;
			break;
		case 'A':
			/* A - Accept incoming call */
			p++;
			isdn_tty_cmd_ATA(info);
			return;
		case 'D':
			/* D - Dial */
			if (info->msr & UART_MSR_DCD)
				PARSE_ERROR;
			if (info->msr & UART_MSR_RI) {
				isdn_tty_modem_result(RESULT_NO_CARRIER, info);
				return;
			}
			isdn_tty_getdial(++p, ds, sizeof ds);
			p += strlen(p);
			if (!strlen(m->msn))
				isdn_tty_modem_result(RESULT_NO_MSN_EAZ, info);
			else if (strlen(ds))
				isdn_tty_dial(ds, info, m);
			else
				PARSE_ERROR;
			return;
		case 'E':
			/* E - Turn Echo on/off */
			p++;
			switch (isdn_getnum(&p)) {
			case 0:
				m->mdmreg[REG_ECHO] &= ~BIT_ECHO;
				break;
			case 1:
				m->mdmreg[REG_ECHO] |= BIT_ECHO;
				break;
			default:
				PARSE_ERROR;
			}
			break;
		case 'H':
			/* H - On/Off-hook */
			p++;
			switch (*p) {
			case '0':
				p++;
				isdn_tty_on_hook(info);
				break;
			case '1':
				p++;
				isdn_tty_off_hook();
				break;
			default:
				isdn_tty_on_hook(info);
				break;
			}
			break;
		case 'I':
			/* I - Information */
			p++;
			isdn_tty_at_cout("\r\nLinux ISDN", info);
			switch (*p) {
			case '0':
			case '1':
				p++;
				break;
			case '2':
				p++;
				isdn_tty_report(info);
				break;
			case '3':
				p++;
				snprintf(ds, sizeof(ds), "\r\n%d", info->emu.charge);
				isdn_tty_at_cout(ds, info);
				break;
			default:;
			}
			break;
#ifdef DUMMY_HAYES_AT
		case 'L':
		case 'M':
			/* only for be compilant with common scripts */
			/* no function */
			p++;
			isdn_getnum(&p);
			break;
#endif
		case 'O':
			/* O - Go online */
			p++;
			if (info->msr & UART_MSR_DCD)
				/* if B-Channel is up */
				isdn_tty_modem_result((m->mdmreg[REG_L2PROT] == ISDN_PROTO_L2_MODEM) ? RESULT_CONNECT : RESULT_CONNECT64000, info);
			else
				isdn_tty_modem_result(RESULT_NO_CARRIER, info);
			return;
		case 'Q':
			/* Q - Turn Emulator messages on/off */
			p++;
			switch (isdn_getnum(&p)) {
			case 0:
				m->mdmreg[REG_RESP] |= BIT_RESP;
				break;
			case 1:
				m->mdmreg[REG_RESP] &= ~BIT_RESP;
				break;
			default:
				PARSE_ERROR;
			}
			break;
		case 'S':
			/* S - Set/Get Register */
			p++;
			if (isdn_tty_cmd_ATS(&p, info))
				return;
			break;
		case 'V':
			/* V - Numeric or ASCII Emulator-messages */
			p++;
			switch (isdn_getnum(&p)) {
			case 0:
				m->mdmreg[REG_RESP] |= BIT_RESPNUM;
				break;
			case 1:
				m->mdmreg[REG_RESP] &= ~BIT_RESPNUM;
				break;
			default:
				PARSE_ERROR;
			}
			break;
		case 'Z':
			/* Z - Load Registers from Profile */
			p++;
			if (info->msr & UART_MSR_DCD) {
				info->online = 0;
				isdn_tty_on_hook(info);
			}
			isdn_tty_modem_reset_regs(info, 1);
			break;
		case '+':
			p++;
			switch (*p) {
#ifdef CONFIG_ISDN_AUDIO
			case 'F':
				p++;
				if (isdn_tty_cmd_PLUSF(&p, info))
					return;
				break;
			case 'V':
				if ((!(m->mdmreg[REG_SI1] & 1)) ||
				    (m->mdmreg[REG_L2PROT] == ISDN_PROTO_L2_MODEM))
					PARSE_ERROR;
				p++;
				if (isdn_tty_cmd_PLUSV(&p, info))
					return;
				break;
#endif                          /* CONFIG_ISDN_AUDIO */
			case 'S':	/* SUSPEND */
				p++;
				isdn_tty_get_msnstr(ds, &p);
				isdn_tty_suspend(ds, info, m);
				break;
			case 'R':	/* RESUME */
				p++;
				isdn_tty_get_msnstr(ds, &p);
				isdn_tty_resume(ds, info, m);
				break;
			case 'M':	/* MESSAGE */
				p++;
				isdn_tty_send_msg(info, m, p);
				break;
			default:
				PARSE_ERROR;
			}
			break;
		case '&':
			p++;
			if (isdn_tty_cmd_ATand(&p, info))
				return;
			break;
		default:
			PARSE_ERROR;
		}
	}
#ifdef CONFIG_ISDN_AUDIO
	if (!info->vonline)
#endif
		isdn_tty_modem_result(RESULT_OK, info);
}