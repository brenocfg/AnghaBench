#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scsi_cmnd {int /*<<< orphan*/  eh_entry; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 

void scsi_eh_finish_cmd(struct scsi_cmnd *scmd, struct list_head *done_q)
{
	list_move_tail(&scmd->eh_entry, done_q);
}