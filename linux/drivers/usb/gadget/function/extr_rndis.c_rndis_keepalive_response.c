#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rndis_params {int /*<<< orphan*/  v; int /*<<< orphan*/  (* resp_avail ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ buf; } ;
typedef  TYPE_1__ rndis_resp_t ;
struct TYPE_7__ {int /*<<< orphan*/  RequestID; } ;
typedef  TYPE_2__ rndis_keepalive_msg_type ;
struct TYPE_8__ {void* Status; int /*<<< orphan*/  RequestID; void* MessageLength; void* MessageType; } ;
typedef  TYPE_3__ rndis_keepalive_cmplt_type ;

/* Variables and functions */
 int ENOMEM ; 
 int RNDIS_MSG_KEEPALIVE_C ; 
 int RNDIS_STATUS_SUCCESS ; 
 void* cpu_to_le32 (int) ; 
 TYPE_1__* rndis_add_response (struct rndis_params*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rndis_keepalive_response(struct rndis_params *params,
				    rndis_keepalive_msg_type *buf)
{
	rndis_keepalive_cmplt_type *resp;
	rndis_resp_t *r;

	/* host "should" check only in RNDIS_DATA_INITIALIZED state */

	r = rndis_add_response(params, sizeof(rndis_keepalive_cmplt_type));
	if (!r)
		return -ENOMEM;
	resp = (rndis_keepalive_cmplt_type *)r->buf;

	resp->MessageType = cpu_to_le32(RNDIS_MSG_KEEPALIVE_C);
	resp->MessageLength = cpu_to_le32(16);
	resp->RequestID = buf->RequestID; /* Still LE in msg buffer */
	resp->Status = cpu_to_le32(RNDIS_STATUS_SUCCESS);

	params->resp_avail(params->v);
	return 0;
}