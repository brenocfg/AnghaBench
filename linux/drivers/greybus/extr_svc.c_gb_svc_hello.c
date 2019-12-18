#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gb_svc_hello_request {int /*<<< orphan*/  interface_id; int /*<<< orphan*/  endo_id; } ;
struct gb_svc {int /*<<< orphan*/  dev; int /*<<< orphan*/  ap_intf_id; int /*<<< orphan*/  endo_id; } ;
struct gb_operation {TYPE_1__* request; struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;
struct TYPE_2__ {int payload_size; struct gb_svc_hello_request* payload; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 struct gb_svc* gb_connection_get_data (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_svc_debugfs_init (struct gb_svc*) ; 
 int gb_svc_queue_deferred_request (struct gb_operation*) ; 
 int gb_svc_watchdog_create (struct gb_svc*) ; 
 int /*<<< orphan*/  gb_svc_watchdog_destroy (struct gb_svc*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_svc_hello(struct gb_operation *op)
{
	struct gb_connection *connection = op->connection;
	struct gb_svc *svc = gb_connection_get_data(connection);
	struct gb_svc_hello_request *hello_request;
	int ret;

	if (op->request->payload_size < sizeof(*hello_request)) {
		dev_warn(&svc->dev, "short hello request (%zu < %zu)\n",
			 op->request->payload_size,
			 sizeof(*hello_request));
		return -EINVAL;
	}

	hello_request = op->request->payload;
	svc->endo_id = le16_to_cpu(hello_request->endo_id);
	svc->ap_intf_id = hello_request->interface_id;

	ret = device_add(&svc->dev);
	if (ret) {
		dev_err(&svc->dev, "failed to register svc device: %d\n", ret);
		return ret;
	}

	ret = gb_svc_watchdog_create(svc);
	if (ret) {
		dev_err(&svc->dev, "failed to create watchdog: %d\n", ret);
		goto err_unregister_device;
	}

	gb_svc_debugfs_init(svc);

	return gb_svc_queue_deferred_request(op);

err_unregister_device:
	gb_svc_watchdog_destroy(svc);
	device_del(&svc->dev);
	return ret;
}