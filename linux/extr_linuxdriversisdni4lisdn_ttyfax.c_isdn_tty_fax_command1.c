#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int online; } ;
typedef  TYPE_3__ modem_info ;
struct TYPE_8__ {int cmd; char* para; } ;
struct TYPE_9__ {TYPE_1__ aux; } ;
struct TYPE_11__ {TYPE_2__ parm; } ;
typedef  TYPE_4__ isdn_ctrl ;

/* Variables and functions */
#define  ISDN_FAX_CLASS1_CONNECT 133 
#define  ISDN_FAX_CLASS1_ERROR 132 
#define  ISDN_FAX_CLASS1_FCERROR 131 
#define  ISDN_FAX_CLASS1_NOCARR 130 
#define  ISDN_FAX_CLASS1_OK 129 
#define  ISDN_FAX_CLASS1_QUERY 128 
 int /*<<< orphan*/  isdn_tty_at_cout (char*,TYPE_3__*) ; 

__attribute__((used)) static int
isdn_tty_fax_command1(modem_info *info, isdn_ctrl *c)
{
	static char *msg[] =
		{"OK", "CONNECT", "NO CARRIER", "ERROR", "FCERROR"};

#ifdef ISDN_TTY_FAX_CMD_DEBUG
	printk(KERN_DEBUG "isdn_tty: FCLASS1 cmd(%d)\n", c->parm.aux.cmd);
#endif
	if (c->parm.aux.cmd < ISDN_FAX_CLASS1_QUERY) {
		if (info->online)
			info->online = 1;
		isdn_tty_at_cout("\r\n", info);
		isdn_tty_at_cout(msg[c->parm.aux.cmd], info);
		isdn_tty_at_cout("\r\n", info);
	}
	switch (c->parm.aux.cmd) {
	case ISDN_FAX_CLASS1_CONNECT:
		info->online = 2;
		break;
	case ISDN_FAX_CLASS1_OK:
	case ISDN_FAX_CLASS1_FCERROR:
	case ISDN_FAX_CLASS1_ERROR:
	case ISDN_FAX_CLASS1_NOCARR:
		break;
	case ISDN_FAX_CLASS1_QUERY:
		isdn_tty_at_cout("\r\n", info);
		if (!c->parm.aux.para[0]) {
			isdn_tty_at_cout(msg[ISDN_FAX_CLASS1_ERROR], info);
			isdn_tty_at_cout("\r\n", info);
		} else {
			isdn_tty_at_cout(c->parm.aux.para, info);
			isdn_tty_at_cout("\r\nOK\r\n", info);
		}
		break;
	}
	return (0);
}