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
struct gb_svc_conn_create_request {void* flags; scalar_t__ tc; void* cport2_id; void* intf2_id; void* cport1_id; void* intf1_id; } ;
struct gb_svc {int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SVC_TYPE_CONN_CREATE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gb_svc_conn_create_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int gb_svc_connection_create(struct gb_svc *svc,
			     u8 intf1_id, u16 cport1_id,
			     u8 intf2_id, u16 cport2_id,
			     u8 cport_flags)
{
	struct gb_svc_conn_create_request request;

	request.intf1_id = intf1_id;
	request.cport1_id = cpu_to_le16(cport1_id);
	request.intf2_id = intf2_id;
	request.cport2_id = cpu_to_le16(cport2_id);
	request.tc = 0;		/* TC0 */
	request.flags = cport_flags;

	return gb_operation_sync(svc->connection, GB_SVC_TYPE_CONN_CREATE,
				 &request, sizeof(request), NULL, 0);
}