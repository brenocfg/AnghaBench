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
struct gb_svc_version_response {scalar_t__ major; int /*<<< orphan*/  minor; } ;
struct gb_svc_version_request {scalar_t__ major; int /*<<< orphan*/  minor; } ;
struct gb_svc {scalar_t__ protocol_major; int /*<<< orphan*/  protocol_minor; int /*<<< orphan*/  dev; } ;
struct gb_operation {TYPE_2__* response; TYPE_1__* request; struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;
struct TYPE_4__ {struct gb_svc_version_response* payload; } ;
struct TYPE_3__ {int payload_size; struct gb_svc_version_request* payload; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 scalar_t__ GB_SVC_VERSION_MAJOR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 struct gb_svc* gb_connection_get_data (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_operation_response_alloc (struct gb_operation*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_svc_version_request(struct gb_operation *op)
{
	struct gb_connection *connection = op->connection;
	struct gb_svc *svc = gb_connection_get_data(connection);
	struct gb_svc_version_request *request;
	struct gb_svc_version_response *response;

	if (op->request->payload_size < sizeof(*request)) {
		dev_err(&svc->dev, "short version request (%zu < %zu)\n",
			op->request->payload_size,
			sizeof(*request));
		return -EINVAL;
	}

	request = op->request->payload;

	if (request->major > GB_SVC_VERSION_MAJOR) {
		dev_warn(&svc->dev, "unsupported major version (%u > %u)\n",
			 request->major, GB_SVC_VERSION_MAJOR);
		return -ENOTSUPP;
	}

	svc->protocol_major = request->major;
	svc->protocol_minor = request->minor;

	if (!gb_operation_response_alloc(op, sizeof(*response), GFP_KERNEL))
		return -ENOMEM;

	response = op->response->payload;
	response->major = svc->protocol_major;
	response->minor = svc->protocol_minor;

	return 0;
}