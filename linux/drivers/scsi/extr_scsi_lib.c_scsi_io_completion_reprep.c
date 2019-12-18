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
struct scsi_cmnd {int dummy; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_mq_requeue_cmd (struct scsi_cmnd*) ; 

__attribute__((used)) static void scsi_io_completion_reprep(struct scsi_cmnd *cmd,
				      struct request_queue *q)
{
	/* A new command will be prepared and issued. */
	scsi_mq_requeue_cmd(cmd);
}