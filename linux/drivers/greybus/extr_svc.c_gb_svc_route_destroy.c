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
typedef  void* u8 ;
struct gb_svc_route_destroy_request {void* intf2_id; void* intf1_id; } ;
struct gb_svc {int /*<<< orphan*/  dev; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SVC_TYPE_ROUTE_DESTROY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,void*,void*,int) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_svc_route_destroy_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void gb_svc_route_destroy(struct gb_svc *svc, u8 intf1_id, u8 intf2_id)
{
	struct gb_svc_route_destroy_request request;
	int ret;

	request.intf1_id = intf1_id;
	request.intf2_id = intf2_id;

	ret = gb_operation_sync(svc->connection, GB_SVC_TYPE_ROUTE_DESTROY,
				&request, sizeof(request), NULL, 0);
	if (ret) {
		dev_err(&svc->dev, "failed to destroy route (%u %u): %d\n",
			intf1_id, intf2_id, ret);
	}
}