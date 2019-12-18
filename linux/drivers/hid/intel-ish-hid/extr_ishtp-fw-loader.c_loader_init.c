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
struct ishtp_fw_client {int dummy; } ;
struct ishtp_cl_data {int /*<<< orphan*/  cl_device; } ;
struct ishtp_cl {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ISHTP_CL_CONNECTING ; 
 int /*<<< orphan*/  LOADER_CL_RX_RING_SIZE ; 
 int /*<<< orphan*/  LOADER_CL_TX_RING_SIZE ; 
 int /*<<< orphan*/  cl_data_to_dev (struct ishtp_cl_data*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ishtp_cl_connect (struct ishtp_cl*) ; 
 int ishtp_cl_link (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_cl_set_fw_client_id (struct ishtp_cl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishtp_cl_unlink (struct ishtp_cl*) ; 
 struct ishtp_fw_client* ishtp_fw_cl_get_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ishtp_cl_data* ishtp_get_client_data (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_get_fw_client_id (struct ishtp_fw_client*) ; 
 int /*<<< orphan*/  ishtp_get_ishtp_device (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_register_event_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishtp_set_connection_state (struct ishtp_cl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishtp_set_rx_ring_size (struct ishtp_cl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishtp_set_tx_ring_size (struct ishtp_cl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loader_cl_event_cb ; 
 int /*<<< orphan*/  loader_ishtp_guid ; 

__attribute__((used)) static int loader_init(struct ishtp_cl *loader_ishtp_cl, int reset)
{
	int rv;
	struct ishtp_fw_client *fw_client;
	struct ishtp_cl_data *client_data =
		ishtp_get_client_data(loader_ishtp_cl);

	dev_dbg(cl_data_to_dev(client_data), "reset flag: %d\n", reset);

	rv = ishtp_cl_link(loader_ishtp_cl);
	if (rv < 0) {
		dev_err(cl_data_to_dev(client_data), "ishtp_cl_link failed\n");
		return rv;
	}

	/* Connect to firmware client */
	ishtp_set_tx_ring_size(loader_ishtp_cl, LOADER_CL_TX_RING_SIZE);
	ishtp_set_rx_ring_size(loader_ishtp_cl, LOADER_CL_RX_RING_SIZE);

	fw_client =
		ishtp_fw_cl_get_client(ishtp_get_ishtp_device(loader_ishtp_cl),
				       &loader_ishtp_guid);
	if (!fw_client) {
		dev_err(cl_data_to_dev(client_data),
			"ISH client uuid not found\n");
		rv = -ENOENT;
		goto err_cl_unlink;
	}

	ishtp_cl_set_fw_client_id(loader_ishtp_cl,
				  ishtp_get_fw_client_id(fw_client));
	ishtp_set_connection_state(loader_ishtp_cl, ISHTP_CL_CONNECTING);

	rv = ishtp_cl_connect(loader_ishtp_cl);
	if (rv < 0) {
		dev_err(cl_data_to_dev(client_data), "Client connect fail\n");
		goto err_cl_unlink;
	}

	dev_dbg(cl_data_to_dev(client_data), "Client connected\n");

	ishtp_register_event_cb(client_data->cl_device, loader_cl_event_cb);

	return 0;

err_cl_unlink:
	ishtp_cl_unlink(loader_ishtp_cl);
	return rv;
}