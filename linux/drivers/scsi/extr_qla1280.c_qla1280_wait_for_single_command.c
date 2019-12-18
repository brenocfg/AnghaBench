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
struct srb {int /*<<< orphan*/ * wait; } ;
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int _qla1280_wait_for_single_command (struct scsi_qla_host*,struct srb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int
qla1280_wait_for_single_command(struct scsi_qla_host *ha, struct srb *sp)
{
	DECLARE_COMPLETION_ONSTACK(wait);

	sp->wait = &wait;
	return _qla1280_wait_for_single_command(ha, sp, &wait);
}