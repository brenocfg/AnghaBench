#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {unsigned char* message; int /*<<< orphan*/  phase; int /*<<< orphan*/  msgs; } ;
struct TYPE_13__ {TYPE_2__ scsi; TYPE_1__* host; } ;
struct TYPE_11__ {int /*<<< orphan*/  host_no; } ;
typedef  TYPE_3__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MSGACCEPTED ; 
 int /*<<< orphan*/  CMD_SETATN ; 
 unsigned char EXTENDED_MESSAGE ; 
 int /*<<< orphan*/  MSG_PARITY_ERROR ; 
 int /*<<< orphan*/  PHASE_MSGOUT_EXPECT ; 
 int /*<<< orphan*/  REG_FF ; 
 int /*<<< orphan*/  fas216_checkmagic (TYPE_3__*) ; 
 int /*<<< orphan*/  fas216_cmd (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int fas216_get_msg_byte (TYPE_3__*) ; 
 int /*<<< orphan*/  fas216_parse_message (TYPE_3__*,unsigned char*,unsigned int) ; 
 unsigned char fas216_readb (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fas216_target (TYPE_3__*) ; 
 int /*<<< orphan*/  msgqueue_addmsg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgqueue_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void fas216_message(FAS216_Info *info)
{
	unsigned char *message = info->scsi.message;
	unsigned int msglen = 1;
	int msgbyte = 0;

	fas216_checkmagic(info);

	message[0] = fas216_readb(info, REG_FF);

	if (message[0] == EXTENDED_MESSAGE) {
		msgbyte = fas216_get_msg_byte(info);

		if (msgbyte >= 0) {
			message[1] = msgbyte;

			for (msglen = 2; msglen < message[1] + 2; msglen++) {
				msgbyte = fas216_get_msg_byte(info);

				if (msgbyte >= 0)
					message[msglen] = msgbyte;
				else
					break;
			}
		}
	}

	if (msgbyte == -3)
		goto parity_error;

#ifdef DEBUG_MESSAGES
	{
		int i;

		printk("scsi%d.%c: message in: ",
			info->host->host_no, fas216_target(info));
		for (i = 0; i < msglen; i++)
			printk("%02X ", message[i]);
		printk("\n");
	}
#endif

	fas216_parse_message(info, message, msglen);
	fas216_cmd(info, CMD_MSGACCEPTED);
	return;

parity_error:
	fas216_cmd(info, CMD_SETATN);
	msgqueue_flush(&info->scsi.msgs);
	msgqueue_addmsg(&info->scsi.msgs, 1, MSG_PARITY_ERROR);
	info->scsi.phase = PHASE_MSGOUT_EXPECT;
	fas216_cmd(info, CMD_MSGACCEPTED);
	return;
}