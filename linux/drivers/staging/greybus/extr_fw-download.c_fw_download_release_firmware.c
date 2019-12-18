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
struct gb_operation {TYPE_1__* request; struct gb_connection* connection; } ;
struct gb_fw_download_release_firmware_request {int /*<<< orphan*/  firmware_id; } ;
struct gb_connection {int dummy; } ;
struct fw_request {int /*<<< orphan*/  dwork; } ;
struct fw_download {int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int payload_size; struct gb_fw_download_release_firmware_request* payload; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  free_firmware (struct fw_download*,struct fw_request*) ; 
 struct fw_download* gb_connection_get_data (struct gb_connection*) ; 
 struct fw_request* get_fw_req (struct fw_download*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_fw_req (struct fw_request*) ; 

__attribute__((used)) static int fw_download_release_firmware(struct gb_operation *op)
{
	struct gb_connection *connection = op->connection;
	struct fw_download *fw_download = gb_connection_get_data(connection);
	struct gb_fw_download_release_firmware_request *request;
	struct fw_request *fw_req;
	u8 firmware_id;

	if (op->request->payload_size != sizeof(*request)) {
		dev_err(fw_download->parent,
			"Illegal size of release firmware request (%zu %zu)\n",
			op->request->payload_size, sizeof(*request));
		return -EINVAL;
	}

	request = op->request->payload;
	firmware_id = request->firmware_id;

	fw_req = get_fw_req(fw_download, firmware_id);
	if (!fw_req) {
		dev_err(fw_download->parent,
			"firmware not available for id: %02u\n", firmware_id);
		return -EINVAL;
	}

	cancel_delayed_work_sync(&fw_req->dwork);

	free_firmware(fw_download, fw_req);
	put_fw_req(fw_req);

	dev_dbg(fw_download->parent, "release firmware\n");

	return 0;
}