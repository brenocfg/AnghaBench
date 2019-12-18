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
struct gb_svc_intf_device_id_request {void* device_id; void* intf_id; } ;
struct gb_svc {int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SVC_TYPE_INTF_DEVICE_ID ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_svc_intf_device_id_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int gb_svc_intf_device_id(struct gb_svc *svc, u8 intf_id, u8 device_id)
{
	struct gb_svc_intf_device_id_request request;

	request.intf_id = intf_id;
	request.device_id = device_id;

	return gb_operation_sync(svc->connection, GB_SVC_TYPE_INTF_DEVICE_ID,
				 &request, sizeof(request), NULL, 0);
}