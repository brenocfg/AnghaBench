#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {scalar_t__ cmd_len; int /*<<< orphan*/ * cmnd; } ;

/* Variables and functions */
 scalar_t__ CMD_I ; 
 TYPE_1__* CURRENT_SC ; 
 int /*<<< orphan*/  SCSIDAT ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIORDY ; 
 int /*<<< orphan*/  SSTAT0 ; 
 scalar_t__ TESTLO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_run(struct Scsi_Host *shpnt)
{
	while(CMD_I<CURRENT_SC->cmd_len) {
		if (TESTLO(SSTAT0, SPIORDY))
			return;

		SETPORT(SCSIDAT, CURRENT_SC->cmnd[CMD_I++]);
	}
}