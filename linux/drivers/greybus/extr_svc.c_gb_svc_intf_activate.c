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
typedef  int /*<<< orphan*/  u8 ;
struct gb_svc_intf_activate_response {scalar_t__ status; int /*<<< orphan*/  intf_type; } ;
struct gb_svc_intf_activate_request {int /*<<< orphan*/  intf_id; } ;
struct gb_svc {int /*<<< orphan*/  dev; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  response ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int EREMOTEIO ; 
 scalar_t__ GB_SVC_OP_SUCCESS ; 
 int /*<<< orphan*/  GB_SVC_TYPE_INTF_ACTIVATE ; 
 int /*<<< orphan*/  SVC_INTF_ACTIVATE_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int gb_operation_sync_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_svc_intf_activate_request*,int,struct gb_svc_intf_activate_response*,int,int /*<<< orphan*/ ) ; 

int gb_svc_intf_activate(struct gb_svc *svc, u8 intf_id, u8 *intf_type)
{
	struct gb_svc_intf_activate_request request;
	struct gb_svc_intf_activate_response response;
	int ret;

	request.intf_id = intf_id;

	ret = gb_operation_sync_timeout(svc->connection,
					GB_SVC_TYPE_INTF_ACTIVATE,
					&request, sizeof(request),
					&response, sizeof(response),
					SVC_INTF_ACTIVATE_TIMEOUT);
	if (ret < 0)
		return ret;
	if (response.status != GB_SVC_OP_SUCCESS) {
		dev_err(&svc->dev, "failed to activate interface %u: %u\n",
			intf_id, response.status);
		return -EREMOTEIO;
	}

	*intf_type = response.intf_type;

	return 0;
}