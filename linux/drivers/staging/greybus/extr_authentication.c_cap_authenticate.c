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
typedef  int u32 ;
struct gb_operation {TYPE_2__* response; TYPE_1__* request; } ;
struct gb_connection {int dummy; } ;
struct gb_cap_authenticate_response {int /*<<< orphan*/ * signature; int /*<<< orphan*/ * response; int /*<<< orphan*/  result_code; } ;
struct gb_cap_authenticate_request {int /*<<< orphan*/ * challenge; int /*<<< orphan*/ * uid; int /*<<< orphan*/  auth_type; } ;
struct gb_cap {int /*<<< orphan*/  parent; struct gb_connection* connection; } ;
struct TYPE_4__ {int payload_size; struct gb_cap_authenticate_response* payload; } ;
struct TYPE_3__ {struct gb_cap_authenticate_request* payload; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GB_CAP_TYPE_AUTHENTICATE ; 
 int /*<<< orphan*/  GB_OPERATION_FLAG_SHORT_RESPONSE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct gb_operation* gb_operation_create_flags (struct gb_connection*,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t gb_operation_get_payload_size_max (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_operation_put (struct gb_operation*) ; 
 int gb_operation_request_send_sync (struct gb_operation*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cap_authenticate(struct gb_cap *cap, u32 auth_type, u8 *uid,
			    u8 *challenge, u8 *result, u8 *auth_response,
			    u32 *signature_size, u8 *signature)
{
	struct gb_connection *connection = cap->connection;
	struct gb_cap_authenticate_request *request;
	struct gb_cap_authenticate_response *response;
	size_t max_size = gb_operation_get_payload_size_max(connection);
	struct gb_operation *op;
	int ret;

	op = gb_operation_create_flags(connection, GB_CAP_TYPE_AUTHENTICATE,
				       sizeof(*request), max_size,
				       GB_OPERATION_FLAG_SHORT_RESPONSE,
				       GFP_KERNEL);
	if (!op)
		return -ENOMEM;

	request = op->request->payload;
	request->auth_type = cpu_to_le32(auth_type);
	memcpy(request->uid, uid, sizeof(request->uid));
	memcpy(request->challenge, challenge, sizeof(request->challenge));

	ret = gb_operation_request_send_sync(op);
	if (ret) {
		dev_err(cap->parent, "failed to authenticate (%d)\n", ret);
		goto done;
	}

	response = op->response->payload;
	*result = response->result_code;
	*signature_size = op->response->payload_size - sizeof(*response);
	memcpy(auth_response, response->response, sizeof(response->response));
	memcpy(signature, response->signature, *signature_size);

done:
	gb_operation_put(op);
	return ret;
}