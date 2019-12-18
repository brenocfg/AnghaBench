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
typedef  int u16 ;
struct gb_operation {int type; TYPE_2__* request; struct gb_connection* connection; } ;
struct gb_log_send_log_request {char* msg; int /*<<< orphan*/  len; } ;
struct gb_connection {TYPE_1__* bundle; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int payload_size; struct gb_log_send_log_request* payload; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int GB_LOG_MAX_LEN ; 
 int GB_LOG_TYPE_SEND_LOG ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_log_request_handler(struct gb_operation *op)
{
	struct gb_connection *connection = op->connection;
	struct device *dev = &connection->bundle->dev;
	struct gb_log_send_log_request *receive;
	u16 len;

	if (op->type != GB_LOG_TYPE_SEND_LOG) {
		dev_err(dev, "unknown request type 0x%02x\n", op->type);
		return -EINVAL;
	}

	/* Verify size of payload */
	if (op->request->payload_size < sizeof(*receive)) {
		dev_err(dev, "log request too small (%zu < %zu)\n",
			op->request->payload_size, sizeof(*receive));
		return -EINVAL;
	}
	receive = op->request->payload;
	len = le16_to_cpu(receive->len);
	if (len != (op->request->payload_size - sizeof(*receive))) {
		dev_err(dev, "log request wrong size %d vs %zu\n", len,
			(op->request->payload_size - sizeof(*receive)));
		return -EINVAL;
	}
	if (len == 0) {
		dev_err(dev, "log request of 0 bytes?\n");
		return -EINVAL;
	}

	if (len > GB_LOG_MAX_LEN) {
		dev_err(dev, "log request too big: %d\n", len);
		return -EINVAL;
	}

	/* Ensure the buffer is 0 terminated */
	receive->msg[len - 1] = '\0';

	/*
	 * Print with dev_dbg() so that it can be easily turned off using
	 * dynamic debugging (and prevent any DoS)
	 */
	dev_dbg(dev, "%s", receive->msg);

	return 0;
}