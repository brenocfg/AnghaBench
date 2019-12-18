#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {TYPE_1__* cmd; } ;
struct sas_task {TYPE_2__ ssp_task; } ;
struct TYPE_3__ {scalar_t__* cmnd; } ;

/* Variables and functions */
 scalar_t__ READ_10 ; 
 scalar_t__ WRITE_10 ; 
 scalar_t__ WRITE_VERIFY ; 

__attribute__((used)) static int check_enc_sas_cmd(struct sas_task *task)
{
	u8 cmd = task->ssp_task.cmd->cmnd[0];

	if (cmd == READ_10 || cmd == WRITE_10 || cmd == WRITE_VERIFY)
		return 1;
	else
		return 0;
}