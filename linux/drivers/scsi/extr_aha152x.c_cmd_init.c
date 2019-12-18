#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {scalar_t__ sent_command; } ;
struct TYPE_5__ {TYPE_1__ SCp; } ;

/* Variables and functions */
 scalar_t__ CMD_I ; 
 TYPE_2__* CURRENT_SC ; 
 int DID_ERROR ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  done (struct Scsi_Host*,int) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 

__attribute__((used)) static void cmd_init(struct Scsi_Host *shpnt)
{
	if (CURRENT_SC->SCp.sent_command) {
		scmd_printk(KERN_ERR, CURRENT_SC,
			    "command already sent\n");
		done(shpnt, DID_ERROR << 16);
		return;
	}

	CMD_I=0;
}