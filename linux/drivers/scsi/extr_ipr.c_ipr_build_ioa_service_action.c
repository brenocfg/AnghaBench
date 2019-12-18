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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  request_type; int /*<<< orphan*/ * cdb; } ;
struct ipr_ioarcb {TYPE_1__ cmd_pkt; int /*<<< orphan*/  res_handle; } ;
struct ipr_cmnd {struct ipr_ioarcb ioarcb; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IPR_IOA_SERVICE_ACTION ; 
 int /*<<< orphan*/  IPR_RQTYPE_IOACMD ; 

__attribute__((used)) static void ipr_build_ioa_service_action(struct ipr_cmnd *ipr_cmd,
					 __be32 res_handle, u8 sa_code)
{
	struct ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;

	ioarcb->res_handle = res_handle;
	ioarcb->cmd_pkt.cdb[0] = IPR_IOA_SERVICE_ACTION;
	ioarcb->cmd_pkt.cdb[1] = sa_code;
	ioarcb->cmd_pkt.request_type = IPR_RQTYPE_IOACMD;
}