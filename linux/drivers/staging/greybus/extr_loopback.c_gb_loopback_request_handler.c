#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gb_operation {int type; TYPE_3__* response; TYPE_2__* request; struct gb_connection* connection; } ;
struct gb_loopback_transfer_response {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct gb_loopback_transfer_request {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct gb_connection {TYPE_1__* bundle; } ;
struct device {int dummy; } ;
struct TYPE_8__ {size_t size_max; } ;
struct TYPE_7__ {struct gb_loopback_transfer_response* payload; } ;
struct TYPE_6__ {int payload_size; struct gb_loopback_transfer_request* payload; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  GB_LOOPBACK_TYPE_PING 130 
#define  GB_LOOPBACK_TYPE_SINK 129 
#define  GB_LOOPBACK_TYPE_TRANSFER 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 TYPE_4__ gb_dev ; 
 int /*<<< orphan*/  gb_operation_response_alloc (struct gb_operation*,size_t,int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int gb_loopback_request_handler(struct gb_operation *operation)
{
	struct gb_connection *connection = operation->connection;
	struct gb_loopback_transfer_request *request;
	struct gb_loopback_transfer_response *response;
	struct device *dev = &connection->bundle->dev;
	size_t len;

	/* By convention, the AP initiates the version operation */
	switch (operation->type) {
	case GB_LOOPBACK_TYPE_PING:
	case GB_LOOPBACK_TYPE_SINK:
		return 0;
	case GB_LOOPBACK_TYPE_TRANSFER:
		if (operation->request->payload_size < sizeof(*request)) {
			dev_err(dev, "transfer request too small (%zu < %zu)\n",
				operation->request->payload_size,
				sizeof(*request));
			return -EINVAL;	/* -EMSGSIZE */
		}
		request = operation->request->payload;
		len = le32_to_cpu(request->len);
		if (len > gb_dev.size_max) {
			dev_err(dev, "transfer request too large (%zu > %zu)\n",
				len, gb_dev.size_max);
			return -EINVAL;
		}

		if (!gb_operation_response_alloc(operation,
				len + sizeof(*response), GFP_KERNEL)) {
			dev_err(dev, "error allocating response\n");
			return -ENOMEM;
		}
		response = operation->response->payload;
		response->len = cpu_to_le32(len);
		if (len)
			memcpy(response->data, request->data, len);

		return 0;
	default:
		dev_err(dev, "unsupported request: %u\n", operation->type);
		return -EINVAL;
	}
}