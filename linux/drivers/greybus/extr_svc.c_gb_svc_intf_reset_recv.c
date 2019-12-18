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
struct gb_svc_intf_reset_request {int dummy; } ;
struct gb_svc {int /*<<< orphan*/  dev; } ;
struct gb_operation {struct gb_message* request; int /*<<< orphan*/  connection; } ;
struct gb_message {int payload_size; struct gb_svc_intf_reset_request* payload; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 struct gb_svc* gb_connection_get_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_svc_intf_reset_recv(struct gb_operation *op)
{
	struct gb_svc *svc = gb_connection_get_data(op->connection);
	struct gb_message *request = op->request;
	struct gb_svc_intf_reset_request *reset;

	if (request->payload_size < sizeof(*reset)) {
		dev_warn(&svc->dev, "short reset request received (%zu < %zu)\n",
			 request->payload_size, sizeof(*reset));
		return -EINVAL;
	}
	reset = request->payload;

	/* FIXME Reset the interface here */

	return 0;
}