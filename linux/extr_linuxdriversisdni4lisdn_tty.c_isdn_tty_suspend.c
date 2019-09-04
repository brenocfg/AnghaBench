#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ isdn_driver; int /*<<< orphan*/  isdn_channel; } ;
typedef  TYPE_4__ modem_info ;
struct TYPE_8__ {scalar_t__ Controller; } ;
struct TYPE_9__ {int Length; int* para; TYPE_1__ adr; int /*<<< orphan*/  Subcommand; int /*<<< orphan*/  Command; } ;
struct TYPE_10__ {TYPE_2__ cmsg; } ;
struct TYPE_12__ {scalar_t__ driver; int /*<<< orphan*/  arg; int /*<<< orphan*/  command; TYPE_3__ parm; } ;
typedef  TYPE_5__ isdn_ctrl ;
typedef  int /*<<< orphan*/  atemu ;

/* Variables and functions */
 int /*<<< orphan*/  CAPI_FACILITY ; 
 int /*<<< orphan*/  CAPI_PUT_MESSAGE ; 
 int /*<<< orphan*/  CAPI_REQ ; 
 int /*<<< orphan*/  isdn_command (TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
isdn_tty_suspend(char *id, modem_info *info, atemu *m)
{
	isdn_ctrl cmd;

	int l;

	if (!info)
		return;

#ifdef ISDN_DEBUG_MODEM_SERVICES
	printk(KERN_DEBUG "Msusp ttyI%d\n", info->line);
#endif
	l = strlen(id);
	if ((info->isdn_driver >= 0)) {
		cmd.parm.cmsg.Length = l + 18;
		cmd.parm.cmsg.Command = CAPI_FACILITY;
		cmd.parm.cmsg.Subcommand = CAPI_REQ;
		cmd.parm.cmsg.adr.Controller = info->isdn_driver + 1;
		cmd.parm.cmsg.para[0] = 3; /* 16 bit 0x0003 suplementary service */
		cmd.parm.cmsg.para[1] = 0;
		cmd.parm.cmsg.para[2] = l + 3;
		cmd.parm.cmsg.para[3] = 4; /* 16 bit 0x0004 Suspend */
		cmd.parm.cmsg.para[4] = 0;
		cmd.parm.cmsg.para[5] = l;
		memcpy(&cmd.parm.cmsg.para[6], id, l);
		cmd.command = CAPI_PUT_MESSAGE;
		cmd.driver = info->isdn_driver;
		cmd.arg = info->isdn_channel;
		isdn_command(&cmd);
	}
}