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
typedef  scalar_t__ u8 ;
struct gb_sdio_host {scalar_t__ removed; int /*<<< orphan*/  mmc; } ;
struct gb_sdio_event_request {scalar_t__ event; } ;
struct gb_operation {scalar_t__ type; struct gb_message* request; int /*<<< orphan*/  connection; } ;
struct gb_message {int payload_size; struct gb_sdio_event_request* payload; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GB_SDIO_TYPE_EVENT ; 
 int /*<<< orphan*/  _gb_queue_event (struct gb_sdio_host*,scalar_t__) ; 
 int _gb_sdio_process_events (struct gb_sdio_host*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 struct gb_sdio_host* gb_connection_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_sdio_request_handler(struct gb_operation *op)
{
	struct gb_sdio_host *host = gb_connection_get_data(op->connection);
	struct gb_message *request;
	struct gb_sdio_event_request *payload;
	u8 type = op->type;
	int ret =  0;
	u8 event;

	if (type != GB_SDIO_TYPE_EVENT) {
		dev_err(mmc_dev(host->mmc),
			"unsupported unsolicited event: %u\n", type);
		return -EINVAL;
	}

	request = op->request;

	if (request->payload_size < sizeof(*payload)) {
		dev_err(mmc_dev(host->mmc), "wrong event size received (%zu < %zu)\n",
			request->payload_size, sizeof(*payload));
		return -EINVAL;
	}

	payload = request->payload;
	event = payload->event;

	if (host->removed)
		_gb_queue_event(host, event);
	else
		ret = _gb_sdio_process_events(host, event);

	return ret;
}