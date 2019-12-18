#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gb_operation {TYPE_3__* response; TYPE_1__* request; } ;
struct gb_connection {int /*<<< orphan*/  name; TYPE_2__* hd; } ;
struct TYPE_6__ {size_t payload_size; void* payload; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {void* payload; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 struct gb_operation* gb_operation_create_flags (struct gb_connection*,int,size_t,size_t,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_operation_put (struct gb_operation*) ; 
 int gb_operation_request_send_sync (struct gb_operation*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__((used)) static int gb_camera_operation_sync_flags(struct gb_connection *connection,
					  int type, unsigned int flags,
					  void *request, size_t request_size,
					  void *response, size_t *response_size)
{
	struct gb_operation *operation;
	int ret;

	operation = gb_operation_create_flags(connection, type, request_size,
					      *response_size, flags,
					      GFP_KERNEL);
	if (!operation)
		return  -ENOMEM;

	if (request_size)
		memcpy(operation->request->payload, request, request_size);

	ret = gb_operation_request_send_sync(operation);
	if (ret) {
		dev_err(&connection->hd->dev,
			"%s: synchronous operation of type 0x%02x failed: %d\n",
			connection->name, type, ret);
	} else {
		*response_size = operation->response->payload_size;

		if (operation->response->payload_size)
			memcpy(response, operation->response->payload,
			       operation->response->payload_size);
	}

	gb_operation_put(operation);

	return ret;
}