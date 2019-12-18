#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int status; int /*<<< orphan*/  done; int /*<<< orphan*/  reply; } ;
struct TYPE_14__ {TYPE_3__ sas_mgmt; int /*<<< orphan*/  reply_sz; } ;
struct TYPE_10__ {int MsgLength; } ;
struct TYPE_11__ {TYPE_1__ reply; } ;
struct TYPE_13__ {TYPE_2__ u; } ;
typedef  TYPE_4__ MPT_FRAME_HDR ;
typedef  TYPE_5__ MPT_ADAPTER ;

/* Variables and functions */
 int MPT_MGMT_STATUS_COMMAND_GOOD ; 
 int MPT_MGMT_STATUS_PENDING ; 
 int MPT_MGMT_STATUS_RF_VALID ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mptsas_mgmt_done(MPT_ADAPTER *ioc, MPT_FRAME_HDR *req,
		MPT_FRAME_HDR *reply)
{
	ioc->sas_mgmt.status |= MPT_MGMT_STATUS_COMMAND_GOOD;
	if (reply != NULL) {
		ioc->sas_mgmt.status |= MPT_MGMT_STATUS_RF_VALID;
		memcpy(ioc->sas_mgmt.reply, reply,
		    min(ioc->reply_sz, 4 * reply->u.reply.MsgLength));
	}

	if (ioc->sas_mgmt.status & MPT_MGMT_STATUS_PENDING) {
		ioc->sas_mgmt.status &= ~MPT_MGMT_STATUS_PENDING;
		complete(&ioc->sas_mgmt.done);
		return 1;
	}
	return 0;
}