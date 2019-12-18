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
struct gb_svc_route_create_request {void* dev2_id; void* intf2_id; void* dev1_id; void* intf1_id; } ;
struct gb_svc {int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SVC_TYPE_ROUTE_CREATE ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_svc_route_create_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int gb_svc_route_create(struct gb_svc *svc, u8 intf1_id, u8 dev1_id,
			u8 intf2_id, u8 dev2_id)
{
	struct gb_svc_route_create_request request;

	request.intf1_id = intf1_id;
	request.dev1_id = dev1_id;
	request.intf2_id = intf2_id;
	request.dev2_id = dev2_id;

	return gb_operation_sync(svc->connection, GB_SVC_TYPE_ROUTE_CREATE,
				 &request, sizeof(request), NULL, 0);
}