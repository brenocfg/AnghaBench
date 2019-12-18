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
struct ishtp_device {int dummy; } ;
struct ishtp_cl_data {int /*<<< orphan*/  cl_device; } ;
struct ishtp_cl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CROS_ISH_CL_RX_RING_SIZE ; 
 int /*<<< orphan*/  CROS_ISH_CL_TX_RING_SIZE ; 
 int ENOENT ; 
 int /*<<< orphan*/  ISHTP_CL_CONNECTING ; 
 int /*<<< orphan*/  cl_data_to_dev (struct ishtp_cl_data*) ; 
 int /*<<< orphan*/  cros_ish_guid ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ish_event_cb ; 
 int ishtp_cl_connect (struct ishtp_cl*) ; 
 int ishtp_cl_link (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_cl_set_fw_client_id (struct ishtp_cl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishtp_cl_unlink (struct ishtp_cl*) ; 
 struct ishtp_fw_client* ishtp_fw_cl_get_client (struct ishtp_device*,int /*<<< orphan*/ *) ; 
 struct ishtp_cl_data* ishtp_get_client_data (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_get_fw_client_id (struct ishtp_fw_client*) ; 
 struct ishtp_device* ishtp_get_ishtp_device (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_register_event_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishtp_set_connection_state (struct ishtp_cl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishtp_set_rx_ring_size (struct ishtp_cl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishtp_set_tx_ring_size (struct ishtp_cl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cros_ish_init(struct ishtp_cl *cros_ish_cl)
{
	int rv;
	struct ishtp_device *dev;
	struct ishtp_fw_client *fw_client;
	struct ishtp_cl_data *client_data = ishtp_get_client_data(cros_ish_cl);

	rv = ishtp_cl_link(cros_ish_cl);
	if (rv) {
		dev_err(cl_data_to_dev(client_data),
			"ishtp_cl_link failed\n");
		return rv;
	}

	dev = ishtp_get_ishtp_device(cros_ish_cl);

	/* Connect to firmware client */
	ishtp_set_tx_ring_size(cros_ish_cl, CROS_ISH_CL_TX_RING_SIZE);
	ishtp_set_rx_ring_size(cros_ish_cl, CROS_ISH_CL_RX_RING_SIZE);

	fw_client = ishtp_fw_cl_get_client(dev, &cros_ish_guid);
	if (!fw_client) {
		dev_err(cl_data_to_dev(client_data),
			"ish client uuid not found\n");
		rv = -ENOENT;
		goto err_cl_unlink;
	}

	ishtp_cl_set_fw_client_id(cros_ish_cl,
				  ishtp_get_fw_client_id(fw_client));
	ishtp_set_connection_state(cros_ish_cl, ISHTP_CL_CONNECTING);

	rv = ishtp_cl_connect(cros_ish_cl);
	if (rv) {
		dev_err(cl_data_to_dev(client_data),
			"client connect fail\n");
		goto err_cl_unlink;
	}

	ishtp_register_event_cb(client_data->cl_device, ish_event_cb);
	return 0;

err_cl_unlink:
	ishtp_cl_unlink(cros_ish_cl);
	return rv;
}