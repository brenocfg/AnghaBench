#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int faxonline; int online; TYPE_2__* fax; } ;
typedef  TYPE_1__ modem_info ;
typedef  int /*<<< orphan*/  isdn_ctrl ;
struct TYPE_9__ {int r_code; int fet; void* phase; int /*<<< orphan*/  direction; } ;
typedef  TYPE_2__ T30_s ;

/* Variables and functions */
 int DLE ; 
 int /*<<< orphan*/  ETX ; 
 void* ISDN_FAX_PHASE_B ; 
 void* ISDN_FAX_PHASE_C ; 
 void* ISDN_FAX_PHASE_D ; 
 void* ISDN_FAX_PHASE_E ; 
#define  ISDN_TTY_FAX_CFR 139 
 int /*<<< orphan*/  ISDN_TTY_FAX_CONN_IN ; 
 int /*<<< orphan*/  ISDN_TTY_FAX_CONN_OUT ; 
#define  ISDN_TTY_FAX_DCS 138 
#define  ISDN_TTY_FAX_DIS 137 
#define  ISDN_TTY_FAX_EOP 136 
#define  ISDN_TTY_FAX_ET 135 
#define  ISDN_TTY_FAX_FCON 134 
#define  ISDN_TTY_FAX_FCON_I 133 
#define  ISDN_TTY_FAX_HNG 132 
#define  ISDN_TTY_FAX_PTS 131 
#define  ISDN_TTY_FAX_RID 130 
#define  ISDN_TTY_FAX_SENT 129 
#define  ISDN_TTY_FAX_TRAIN_OK 128 
 scalar_t__ TTY_IS_FCLASS1 (TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_tty_at_cout (char*,TYPE_1__*) ; 
 int isdn_tty_fax_command1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdn_tty_fax_modem_result (int,TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

int
isdn_tty_fax_command(modem_info *info, isdn_ctrl *c)
{
	T30_s *f = info->fax;
	char rs[10];

	if (TTY_IS_FCLASS1(info))
		return (isdn_tty_fax_command1(info, c));

#ifdef ISDN_TTY_FAX_CMD_DEBUG
	printk(KERN_DEBUG "isdn_tty: Fax cmd %d on ttyI%d\n",
	       f->r_code, info->line);
#endif
	switch (f->r_code) {
	case ISDN_TTY_FAX_FCON:
		info->faxonline = 1;
		isdn_tty_fax_modem_result(2, info);	/* +FCON */
		return (0);
	case ISDN_TTY_FAX_FCON_I:
		info->faxonline = 16;
		isdn_tty_fax_modem_result(2, info);	/* +FCON */
		return (0);
	case ISDN_TTY_FAX_RID:
		if (info->faxonline & 1)
			isdn_tty_fax_modem_result(3, info);	/* +FCSI */
		if (info->faxonline & 16)
			isdn_tty_fax_modem_result(8, info);	/* +FTSI */
		return (0);
	case ISDN_TTY_FAX_DIS:
		isdn_tty_fax_modem_result(4, info);	/* +FDIS */
		return (0);
	case ISDN_TTY_FAX_HNG:
		if (f->phase == ISDN_FAX_PHASE_C) {
			if (f->direction == ISDN_TTY_FAX_CONN_IN) {
				sprintf(rs, "%c%c", DLE, ETX);
				isdn_tty_at_cout(rs, info);
			} else {
				sprintf(rs, "%c", 0x18);
				isdn_tty_at_cout(rs, info);
			}
			info->faxonline &= ~2;	/* leave data mode */
			info->online = 1;
		}
		f->phase = ISDN_FAX_PHASE_E;
		isdn_tty_fax_modem_result(5, info);	/* +FHNG */
		isdn_tty_fax_modem_result(0, info);	/* OK */
		return (0);
	case ISDN_TTY_FAX_DCS:
		isdn_tty_fax_modem_result(6, info);	/* +FDCS */
		isdn_tty_fax_modem_result(7, info);	/* CONNECT */
		f->phase = ISDN_FAX_PHASE_C;
		return (0);
	case ISDN_TTY_FAX_TRAIN_OK:
		isdn_tty_fax_modem_result(6, info);	/* +FDCS */
		isdn_tty_fax_modem_result(0, info);	/* OK */
		return (0);
	case ISDN_TTY_FAX_SENT:
		isdn_tty_fax_modem_result(0, info);	/* OK */
		return (0);
	case ISDN_TTY_FAX_CFR:
		isdn_tty_fax_modem_result(9, info);	/* +FCFR */
		return (0);
	case ISDN_TTY_FAX_ET:
		sprintf(rs, "%c%c", DLE, ETX);
		isdn_tty_at_cout(rs, info);
		isdn_tty_fax_modem_result(10, info);	/* +FPTS */
		isdn_tty_fax_modem_result(11, info);	/* +FET */
		isdn_tty_fax_modem_result(0, info);	/* OK */
		info->faxonline &= ~2;	/* leave data mode */
		info->online = 1;
		f->phase = ISDN_FAX_PHASE_D;
		return (0);
	case ISDN_TTY_FAX_PTS:
		isdn_tty_fax_modem_result(10, info);	/* +FPTS */
		if (f->direction == ISDN_TTY_FAX_CONN_OUT) {
			if (f->fet == 1)
				f->phase = ISDN_FAX_PHASE_B;
			if (f->fet == 0)
				isdn_tty_fax_modem_result(0, info);	/* OK */
		}
		return (0);
	case ISDN_TTY_FAX_EOP:
		info->faxonline &= ~2;	/* leave data mode */
		info->online = 1;
		f->phase = ISDN_FAX_PHASE_D;
		return (0);

	}
	return (-1);
}