#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
struct TYPE_6__ {TYPE_2__ ioasa; } ;
struct ipr_cmnd {int /*<<< orphan*/  job_step; TYPE_3__ s; } ;

/* Variables and functions */
 scalar_t__ IPR_IOASC_IR_INVALID_REQ_TYPE_OR_PKT ; 
 int IPR_RC_JOB_CONTINUE ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_ioafp_mode_sense_page28 ; 
 int ipr_reset_cmd_failed (struct ipr_cmnd*) ; 

__attribute__((used)) static int ipr_reset_mode_sense_page24_failed(struct ipr_cmnd *ipr_cmd)
{
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	if (ioasc == IPR_IOASC_IR_INVALID_REQ_TYPE_OR_PKT) {
		ipr_cmd->job_step = ipr_ioafp_mode_sense_page28;
		return IPR_RC_JOB_CONTINUE;
	}

	return ipr_reset_cmd_failed(ipr_cmd);
}