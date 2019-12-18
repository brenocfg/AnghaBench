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
typedef  int /*<<< orphan*/  u16 ;
struct gb_svc_conn_destroy_request {void* cport2_id; void* intf2_id; void* cport1_id; void* intf1_id; } ;
struct gb_svc {int /*<<< orphan*/  dev; struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SVC_TYPE_CONN_DESTROY ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,struct gb_svc_conn_destroy_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void gb_svc_connection_destroy(struct gb_svc *svc, u8 intf1_id, u16 cport1_id,
			       u8 intf2_id, u16 cport2_id)
{
	struct gb_svc_conn_destroy_request request;
	struct gb_connection *connection = svc->connection;
	int ret;

	request.intf1_id = intf1_id;
	request.cport1_id = cpu_to_le16(cport1_id);
	request.intf2_id = intf2_id;
	request.cport2_id = cpu_to_le16(cport2_id);

	ret = gb_operation_sync(connection, GB_SVC_TYPE_CONN_DESTROY,
				&request, sizeof(request), NULL, 0);
	if (ret) {
		dev_err(&svc->dev, "failed to destroy connection (%u:%u %u:%u): %d\n",
			intf1_id, cport1_id, intf2_id, cport2_id, ret);
	}
}