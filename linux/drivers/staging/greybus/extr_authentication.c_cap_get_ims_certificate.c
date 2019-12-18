#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct gb_operation {TYPE_2__* response; TYPE_1__* request; } ;
struct gb_connection {int dummy; } ;
struct gb_cap_get_ims_certificate_response {int /*<<< orphan*/  certificate; int /*<<< orphan*/  result_code; } ;
struct gb_cap_get_ims_certificate_request {void* certificate_id; void* certificate_class; } ;
struct gb_cap {int /*<<< orphan*/  parent; struct gb_connection* connection; } ;
struct TYPE_4__ {scalar_t__ payload_size; struct gb_cap_get_ims_certificate_response* payload; } ;
struct TYPE_3__ {struct gb_cap_get_ims_certificate_request* payload; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GB_CAP_TYPE_GET_IMS_CERTIFICATE ; 
 int /*<<< orphan*/  GB_OPERATION_FLAG_SHORT_RESPONSE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct gb_operation* gb_operation_create_flags (struct gb_connection*,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t gb_operation_get_payload_size_max (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_operation_put (struct gb_operation*) ; 
 int gb_operation_request_send_sync (struct gb_operation*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int cap_get_ims_certificate(struct gb_cap *cap, u32 class, u32 id,
				   u8 *certificate, u32 *size, u8 *result)
{
	struct gb_connection *connection = cap->connection;
	struct gb_cap_get_ims_certificate_request *request;
	struct gb_cap_get_ims_certificate_response *response;
	size_t max_size = gb_operation_get_payload_size_max(connection);
	struct gb_operation *op;
	int ret;

	op = gb_operation_create_flags(connection,
				       GB_CAP_TYPE_GET_IMS_CERTIFICATE,
				       sizeof(*request), max_size,
				       GB_OPERATION_FLAG_SHORT_RESPONSE,
				       GFP_KERNEL);
	if (!op)
		return -ENOMEM;

	request = op->request->payload;
	request->certificate_class = cpu_to_le32(class);
	request->certificate_id = cpu_to_le32(id);

	ret = gb_operation_request_send_sync(op);
	if (ret) {
		dev_err(cap->parent, "failed to get certificate (%d)\n", ret);
		goto done;
	}

	response = op->response->payload;
	*result = response->result_code;
	*size = op->response->payload_size - sizeof(*response);
	memcpy(certificate, response->certificate, *size);

done:
	gb_operation_put(op);
	return ret;
}