#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct srp_event_struct {TYPE_4__* xfer_iu; struct ibmvscsi_host_data* hostdata; } ;
struct ibmvscsi_host_data {int /*<<< orphan*/  work_wait_q; int /*<<< orphan*/  action; int /*<<< orphan*/  request_limit; scalar_t__ client_migrated; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int opcode; int /*<<< orphan*/  req_lim_delta; } ;
struct TYPE_5__ {int /*<<< orphan*/  reason; } ;
struct TYPE_7__ {TYPE_2__ login_rsp; TYPE_1__ login_rej; } ;
struct TYPE_8__ {TYPE_3__ srp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVSCSI_HOST_ACTION_UNBLOCK ; 
#define  SRP_LOGIN_REJ 129 
#define  SRP_LOGIN_RSP 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void login_rsp(struct srp_event_struct *evt_struct)
{
	struct ibmvscsi_host_data *hostdata = evt_struct->hostdata;
	switch (evt_struct->xfer_iu->srp.login_rsp.opcode) {
	case SRP_LOGIN_RSP:	/* it worked! */
		break;
	case SRP_LOGIN_REJ:	/* refused! */
		dev_info(hostdata->dev, "SRP_LOGIN_REJ reason %u\n",
			 evt_struct->xfer_iu->srp.login_rej.reason);
		/* Login failed.  */
		atomic_set(&hostdata->request_limit, -1);
		return;
	default:
		dev_err(hostdata->dev, "Invalid login response typecode 0x%02x!\n",
			evt_struct->xfer_iu->srp.login_rsp.opcode);
		/* Login failed.  */
		atomic_set(&hostdata->request_limit, -1);
		return;
	}

	dev_info(hostdata->dev, "SRP_LOGIN succeeded\n");
	hostdata->client_migrated = 0;

	/* Now we know what the real request-limit is.
	 * This value is set rather than added to request_limit because
	 * request_limit could have been set to -1 by this client.
	 */
	atomic_set(&hostdata->request_limit,
		   be32_to_cpu(evt_struct->xfer_iu->srp.login_rsp.req_lim_delta));

	/* If we had any pending I/Os, kick them */
	hostdata->action = IBMVSCSI_HOST_ACTION_UNBLOCK;
	wake_up(&hostdata->work_wait_q);
}