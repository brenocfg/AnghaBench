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
typedef  int /*<<< orphan*/  u8 ;
struct gb_svc_intf_oops_request {int /*<<< orphan*/  reason; int /*<<< orphan*/  intf_id; } ;
struct gb_svc {int /*<<< orphan*/  dev; } ;
struct gb_operation {TYPE_1__* request; struct gb_connection* connection; } ;
struct gb_interface {int disconnected; int /*<<< orphan*/  mutex; } ;
struct gb_connection {int dummy; } ;
struct TYPE_2__ {struct gb_svc_intf_oops_request* payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct gb_svc* gb_connection_get_data (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_interface_deactivate (struct gb_interface*) ; 
 int /*<<< orphan*/  gb_interface_disable (struct gb_interface*) ; 
 struct gb_interface* gb_svc_interface_lookup (struct gb_svc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_svc_process_intf_oops(struct gb_operation *operation)
{
	struct gb_svc_intf_oops_request *request;
	struct gb_connection *connection = operation->connection;
	struct gb_svc *svc = gb_connection_get_data(connection);
	struct gb_interface *intf;
	u8 intf_id;
	u8 reason;

	/* The request message size has already been verified. */
	request = operation->request->payload;
	intf_id = request->intf_id;
	reason = request->reason;

	intf = gb_svc_interface_lookup(svc, intf_id);
	if (!intf) {
		dev_warn(&svc->dev, "unexpected interface-oops event %u\n",
			 intf_id);
		return;
	}

	dev_info(&svc->dev, "Deactivating interface %u, interface oops reason = %u\n",
		 intf_id, reason);

	mutex_lock(&intf->mutex);
	intf->disconnected = true;
	gb_interface_disable(intf);
	gb_interface_deactivate(intf);
	mutex_unlock(&intf->mutex);
}