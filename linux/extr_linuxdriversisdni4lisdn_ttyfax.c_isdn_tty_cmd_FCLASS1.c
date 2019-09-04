#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_10__ {int isdn_driver; int isdn_channel; int drv_index; int line; } ;
typedef  TYPE_3__ modem_info ;
struct TYPE_8__ {int cmd; scalar_t__ subcmd; int* para; } ;
struct TYPE_9__ {TYPE_1__ aux; } ;
struct TYPE_11__ {int driver; int arg; TYPE_2__ parm; int /*<<< orphan*/  command; } ;
typedef  TYPE_4__ isdn_ctrl ;
struct TYPE_12__ {int* drvmap; int* chanmap; int* m_idx; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ AT_COMMAND ; 
 scalar_t__ AT_EQ_QUERY ; 
 scalar_t__ AT_EQ_VALUE ; 
 scalar_t__ AT_QUERY ; 
 int /*<<< orphan*/  ISDN_CMD_FAXCMD ; 
 int /*<<< orphan*/  ISDN_PROTO_L2_FAX ; 
 int /*<<< orphan*/  ISDN_PROTO_L3_FCLASS1 ; 
 int /*<<< orphan*/  ISDN_USAGE_FAX ; 
 int /*<<< orphan*/  PARSE_ERROR1 ; 
 TYPE_7__* dev ; 
 int /*<<< orphan*/  isdn_command (TYPE_4__*) ; 
 int /*<<< orphan*/  isdn_free_channel (int,int,int /*<<< orphan*/ ) ; 
 int isdn_get_free_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 
 int isdn_getnum (char**) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int
isdn_tty_cmd_FCLASS1(char **p, modem_info *info)
{
	static char *cmd[] =
		{"AE", "TS", "RS", "TM", "RM", "TH", "RH"};
	isdn_ctrl c;
	int par, i;
	u_long flags;

	for (c.parm.aux.cmd = 0; c.parm.aux.cmd < 7; c.parm.aux.cmd++)
		if (!strncmp(p[0], cmd[c.parm.aux.cmd], 2))
			break;

#ifdef ISDN_TTY_FAX_CMD_DEBUG
	printk(KERN_DEBUG "isdn_tty_cmd_FCLASS1 (%s,%d)\n", p[0], c.parm.aux.cmd);
#endif
	if (c.parm.aux.cmd == 7)
		PARSE_ERROR1;

	p[0] += 2;
	switch (*p[0]) {
	case '?':
		p[0]++;
		c.parm.aux.subcmd = AT_QUERY;
		break;
	case '=':
		p[0]++;
		if (*p[0] == '?') {
			p[0]++;
			c.parm.aux.subcmd = AT_EQ_QUERY;
		} else {
			par = isdn_getnum(p);
			if ((par < 0) || (par > 255))
				PARSE_ERROR1;
			c.parm.aux.subcmd = AT_EQ_VALUE;
			c.parm.aux.para[0] = par;
		}
		break;
	case 0:
		c.parm.aux.subcmd = AT_COMMAND;
		break;
	default:
		PARSE_ERROR1;
	}
	c.command = ISDN_CMD_FAXCMD;
#ifdef ISDN_TTY_FAX_CMD_DEBUG
	printk(KERN_DEBUG "isdn_tty_cmd_FCLASS1 %d/%d/%d)\n",
	       c.parm.aux.cmd, c.parm.aux.subcmd, c.parm.aux.para[0]);
#endif
	if (info->isdn_driver < 0) {
		if ((c.parm.aux.subcmd == AT_EQ_VALUE) ||
		    (c.parm.aux.subcmd == AT_COMMAND)) {
			PARSE_ERROR1;
		}
		spin_lock_irqsave(&dev->lock, flags);
		/* get a temporary connection to the first free fax driver */
		i = isdn_get_free_channel(ISDN_USAGE_FAX, ISDN_PROTO_L2_FAX,
					  ISDN_PROTO_L3_FCLASS1, -1, -1, "00");
		if (i < 0) {
			spin_unlock_irqrestore(&dev->lock, flags);
			PARSE_ERROR1;
		}
		info->isdn_driver = dev->drvmap[i];
		info->isdn_channel = dev->chanmap[i];
		info->drv_index = i;
		dev->m_idx[i] = info->line;
		spin_unlock_irqrestore(&dev->lock, flags);
		c.driver = info->isdn_driver;
		c.arg = info->isdn_channel;
		isdn_command(&c);
		spin_lock_irqsave(&dev->lock, flags);
		isdn_free_channel(info->isdn_driver, info->isdn_channel,
				  ISDN_USAGE_FAX);
		info->isdn_driver = -1;
		info->isdn_channel = -1;
		if (info->drv_index >= 0) {
			dev->m_idx[info->drv_index] = -1;
			info->drv_index = -1;
		}
		spin_unlock_irqrestore(&dev->lock, flags);
	} else {
		c.driver = info->isdn_driver;
		c.arg = info->isdn_channel;
		isdn_command(&c);
	}
	return 1;
}