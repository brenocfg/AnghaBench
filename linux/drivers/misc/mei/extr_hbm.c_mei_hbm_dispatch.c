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
typedef  int /*<<< orphan*/  u8 ;
struct mei_msg_hdr {int length; } ;
struct mei_hbm_cl_cmd {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  minor_version; int /*<<< orphan*/  major_version; } ;
struct mei_device {scalar_t__ hbm_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_state; int /*<<< orphan*/  init_clients_timer; int /*<<< orphan*/  me_clients_map; int /*<<< orphan*/  hbm_f_dr_supported; int /*<<< orphan*/  wait_hbm_start; TYPE_1__ version; scalar_t__ rd_msg_buf; } ;
struct mei_bus_message {int hbm_cmd; } ;
struct hbm_props_response {int /*<<< orphan*/  me_addr; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int /*<<< orphan*/  minor_version; int /*<<< orphan*/  major_version; } ;
struct hbm_host_version_response {TYPE_2__ me_max_version; int /*<<< orphan*/  host_version_supported; } ;
struct hbm_host_enum_response {int /*<<< orphan*/  valid_addresses; } ;
struct hbm_flow_control {int dummy; } ;
struct hbm_dma_setup_response {int /*<<< orphan*/  status; } ;
struct hbm_client_connect_request {int dummy; } ;
struct hbm_add_client_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
#define  CLIENT_CONNECT_RES_CMD 142 
#define  CLIENT_DISCONNECT_REQ_CMD 141 
#define  CLIENT_DISCONNECT_RES_CMD 140 
 int EIO ; 
 int EPROTO ; 
 int /*<<< orphan*/  HBM_MAJOR_VERSION ; 
 int /*<<< orphan*/  HBM_MINOR_VERSION ; 
#define  HOST_CLIENT_PROPERTIES_RES_CMD 139 
#define  HOST_ENUM_RES_CMD 138 
#define  HOST_START_RES_CMD 137 
#define  HOST_STOP_RES_CMD 136 
 int /*<<< orphan*/  MEI_DEV_INIT_CLIENTS ; 
 int /*<<< orphan*/  MEI_DEV_POWER_DOWN ; 
#define  MEI_FLOW_CONTROL_CMD 135 
 int /*<<< orphan*/  MEI_FOP_CONNECT ; 
 int /*<<< orphan*/  MEI_FOP_DISCONNECT ; 
 int /*<<< orphan*/  MEI_HBMS_CLIENT_NOT_FOUND ; 
 int /*<<< orphan*/  MEI_HBMS_NOT_ALLOWED ; 
#define  MEI_HBM_ADD_CLIENT_REQ_CMD 134 
 scalar_t__ MEI_HBM_CLIENT_PROPERTIES ; 
#define  MEI_HBM_DMA_SETUP_RES_CMD 133 
 scalar_t__ MEI_HBM_DR_SETUP ; 
 scalar_t__ MEI_HBM_ENUM_CLIENTS ; 
 scalar_t__ MEI_HBM_IDLE ; 
#define  MEI_HBM_NOTIFICATION_CMD 132 
#define  MEI_HBM_NOTIFY_RES_CMD 131 
 scalar_t__ MEI_HBM_STARTING ; 
 void* MEI_HBM_STOPPED ; 
#define  MEI_PG_ISOLATION_ENTRY_RES_CMD 130 
#define  MEI_PG_ISOLATION_EXIT_REQ_CMD 129 
#define  ME_STOP_REQ_CMD 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mei_dma_ring_is_allocated (struct mei_device*) ; 
 int /*<<< orphan*/  mei_dmam_ring_alloc (struct mei_device*) ; 
 int /*<<< orphan*/  mei_dmam_ring_free (struct mei_device*) ; 
 int /*<<< orphan*/  mei_hbm_cl_notify (struct mei_device*,struct mei_hbm_cl_cmd*) ; 
 int /*<<< orphan*/  mei_hbm_cl_res (struct mei_device*,struct mei_hbm_cl_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_hbm_cl_tx_flow_ctrl_creds_res (struct mei_device*,struct hbm_flow_control*) ; 
 int /*<<< orphan*/  mei_hbm_config_features (struct mei_device*) ; 
 int /*<<< orphan*/  mei_hbm_dma_setup_req (struct mei_device*) ; 
 int /*<<< orphan*/  mei_hbm_enum_clients_req (struct mei_device*) ; 
 int mei_hbm_fw_add_cl_req (struct mei_device*,struct hbm_add_client_request*) ; 
 int /*<<< orphan*/  mei_hbm_fw_disconnect_req (struct mei_device*,struct hbm_client_connect_request*) ; 
 int /*<<< orphan*/  mei_hbm_me_cl_add (struct mei_device*,struct hbm_props_response*) ; 
 int mei_hbm_pg_enter_res (struct mei_device*) ; 
 int mei_hbm_pg_exit_res (struct mei_device*) ; 
 int /*<<< orphan*/  mei_hbm_prop_req (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_hbm_status_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_hbm_stop_req (struct mei_device*) ; 
 int /*<<< orphan*/  mei_hbm_version_is_supported (struct mei_device*) ; 
 int /*<<< orphan*/  mei_read_slots (struct mei_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notify_res_to_fop (struct mei_hbm_cl_cmd*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int mei_hbm_dispatch(struct mei_device *dev, struct mei_msg_hdr *hdr)
{
	struct mei_bus_message *mei_msg;
	struct hbm_host_version_response *version_res;
	struct hbm_props_response *props_res;
	struct hbm_host_enum_response *enum_res;
	struct hbm_dma_setup_response *dma_setup_res;
	struct hbm_add_client_request *add_cl_req;
	int ret;

	struct mei_hbm_cl_cmd *cl_cmd;
	struct hbm_client_connect_request *disconnect_req;
	struct hbm_flow_control *fctrl;

	/* read the message to our buffer */
	BUG_ON(hdr->length >= sizeof(dev->rd_msg_buf));
	mei_read_slots(dev, dev->rd_msg_buf, hdr->length);
	mei_msg = (struct mei_bus_message *)dev->rd_msg_buf;
	cl_cmd  = (struct mei_hbm_cl_cmd *)mei_msg;

	/* ignore spurious message and prevent reset nesting
	 * hbm is put to idle during system reset
	 */
	if (dev->hbm_state == MEI_HBM_IDLE) {
		dev_dbg(dev->dev, "hbm: state is idle ignore spurious messages\n");
		return 0;
	}

	switch (mei_msg->hbm_cmd) {
	case HOST_START_RES_CMD:
		dev_dbg(dev->dev, "hbm: start: response message received.\n");

		dev->init_clients_timer = 0;

		version_res = (struct hbm_host_version_response *)mei_msg;

		dev_dbg(dev->dev, "HBM VERSION: DRIVER=%02d:%02d DEVICE=%02d:%02d\n",
				HBM_MAJOR_VERSION, HBM_MINOR_VERSION,
				version_res->me_max_version.major_version,
				version_res->me_max_version.minor_version);

		if (version_res->host_version_supported) {
			dev->version.major_version = HBM_MAJOR_VERSION;
			dev->version.minor_version = HBM_MINOR_VERSION;
		} else {
			dev->version.major_version =
				version_res->me_max_version.major_version;
			dev->version.minor_version =
				version_res->me_max_version.minor_version;
		}

		if (!mei_hbm_version_is_supported(dev)) {
			dev_warn(dev->dev, "hbm: start: version mismatch - stopping the driver.\n");

			dev->hbm_state = MEI_HBM_STOPPED;
			if (mei_hbm_stop_req(dev)) {
				dev_err(dev->dev, "hbm: start: failed to send stop request\n");
				return -EIO;
			}
			break;
		}

		mei_hbm_config_features(dev);

		if (dev->dev_state != MEI_DEV_INIT_CLIENTS ||
		    dev->hbm_state != MEI_HBM_STARTING) {
			dev_err(dev->dev, "hbm: start: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			return -EPROTO;
		}

		if (dev->hbm_f_dr_supported) {
			if (mei_dmam_ring_alloc(dev))
				dev_info(dev->dev, "running w/o dma ring\n");
			if (mei_dma_ring_is_allocated(dev)) {
				if (mei_hbm_dma_setup_req(dev))
					return -EIO;

				wake_up(&dev->wait_hbm_start);
				break;
			}
		}

		dev->hbm_f_dr_supported = 0;
		mei_dmam_ring_free(dev);

		if (mei_hbm_enum_clients_req(dev))
			return -EIO;

		wake_up(&dev->wait_hbm_start);
		break;

	case MEI_HBM_DMA_SETUP_RES_CMD:
		dev_dbg(dev->dev, "hbm: dma setup response: message received.\n");

		dev->init_clients_timer = 0;

		if (dev->hbm_state != MEI_HBM_DR_SETUP) {
			dev_err(dev->dev, "hbm: dma setup response: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			return -EPROTO;
		}

		dma_setup_res = (struct hbm_dma_setup_response *)mei_msg;

		if (dma_setup_res->status) {
			u8 status = dma_setup_res->status;

			if (status == MEI_HBMS_NOT_ALLOWED) {
				dev_dbg(dev->dev, "hbm: dma setup not allowed\n");
			} else {
				dev_info(dev->dev, "hbm: dma setup response: failure = %d %s\n",
					 status,
					 mei_hbm_status_str(status));
			}
			dev->hbm_f_dr_supported = 0;
			mei_dmam_ring_free(dev);
		}

		if (mei_hbm_enum_clients_req(dev))
			return -EIO;
		break;

	case CLIENT_CONNECT_RES_CMD:
		dev_dbg(dev->dev, "hbm: client connect response: message received.\n");
		mei_hbm_cl_res(dev, cl_cmd, MEI_FOP_CONNECT);
		break;

	case CLIENT_DISCONNECT_RES_CMD:
		dev_dbg(dev->dev, "hbm: client disconnect response: message received.\n");
		mei_hbm_cl_res(dev, cl_cmd, MEI_FOP_DISCONNECT);
		break;

	case MEI_FLOW_CONTROL_CMD:
		dev_dbg(dev->dev, "hbm: client flow control response: message received.\n");

		fctrl = (struct hbm_flow_control *)mei_msg;
		mei_hbm_cl_tx_flow_ctrl_creds_res(dev, fctrl);
		break;

	case MEI_PG_ISOLATION_ENTRY_RES_CMD:
		dev_dbg(dev->dev, "hbm: power gate isolation entry response received\n");
		ret = mei_hbm_pg_enter_res(dev);
		if (ret)
			return ret;
		break;

	case MEI_PG_ISOLATION_EXIT_REQ_CMD:
		dev_dbg(dev->dev, "hbm: power gate isolation exit request received\n");
		ret = mei_hbm_pg_exit_res(dev);
		if (ret)
			return ret;
		break;

	case HOST_CLIENT_PROPERTIES_RES_CMD:
		dev_dbg(dev->dev, "hbm: properties response: message received.\n");

		dev->init_clients_timer = 0;

		if (dev->dev_state != MEI_DEV_INIT_CLIENTS ||
		    dev->hbm_state != MEI_HBM_CLIENT_PROPERTIES) {
			dev_err(dev->dev, "hbm: properties response: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			return -EPROTO;
		}

		props_res = (struct hbm_props_response *)mei_msg;

		if (props_res->status == MEI_HBMS_CLIENT_NOT_FOUND) {
			dev_dbg(dev->dev, "hbm: properties response: %d CLIENT_NOT_FOUND\n",
				props_res->me_addr);
		} else if (props_res->status) {
			dev_err(dev->dev, "hbm: properties response: wrong status = %d %s\n",
				props_res->status,
				mei_hbm_status_str(props_res->status));
			return -EPROTO;
		} else {
			mei_hbm_me_cl_add(dev, props_res);
		}

		/* request property for the next client */
		if (mei_hbm_prop_req(dev, props_res->me_addr + 1))
			return -EIO;

		break;

	case HOST_ENUM_RES_CMD:
		dev_dbg(dev->dev, "hbm: enumeration response: message received\n");

		dev->init_clients_timer = 0;

		enum_res = (struct hbm_host_enum_response *) mei_msg;
		BUILD_BUG_ON(sizeof(dev->me_clients_map)
				< sizeof(enum_res->valid_addresses));
		memcpy(dev->me_clients_map, enum_res->valid_addresses,
				sizeof(enum_res->valid_addresses));

		if (dev->dev_state != MEI_DEV_INIT_CLIENTS ||
		    dev->hbm_state != MEI_HBM_ENUM_CLIENTS) {
			dev_err(dev->dev, "hbm: enumeration response: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			return -EPROTO;
		}

		dev->hbm_state = MEI_HBM_CLIENT_PROPERTIES;

		/* first property request */
		if (mei_hbm_prop_req(dev, 0))
			return -EIO;

		break;

	case HOST_STOP_RES_CMD:
		dev_dbg(dev->dev, "hbm: stop response: message received\n");

		dev->init_clients_timer = 0;

		if (dev->hbm_state != MEI_HBM_STOPPED) {
			dev_err(dev->dev, "hbm: stop response: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			return -EPROTO;
		}

		dev->dev_state = MEI_DEV_POWER_DOWN;
		dev_info(dev->dev, "hbm: stop response: resetting.\n");
		/* force the reset */
		return -EPROTO;
		break;

	case CLIENT_DISCONNECT_REQ_CMD:
		dev_dbg(dev->dev, "hbm: disconnect request: message received\n");

		disconnect_req = (struct hbm_client_connect_request *)mei_msg;
		mei_hbm_fw_disconnect_req(dev, disconnect_req);
		break;

	case ME_STOP_REQ_CMD:
		dev_dbg(dev->dev, "hbm: stop request: message received\n");
		dev->hbm_state = MEI_HBM_STOPPED;
		if (mei_hbm_stop_req(dev)) {
			dev_err(dev->dev, "hbm: stop request: failed to send stop request\n");
			return -EIO;
		}
		break;

	case MEI_HBM_ADD_CLIENT_REQ_CMD:
		dev_dbg(dev->dev, "hbm: add client request received\n");
		/*
		 * after the host receives the enum_resp
		 * message clients may be added or removed
		 */
		if (dev->hbm_state <= MEI_HBM_ENUM_CLIENTS ||
		    dev->hbm_state >= MEI_HBM_STOPPED) {
			dev_err(dev->dev, "hbm: add client: state mismatch, [%d, %d]\n",
				dev->dev_state, dev->hbm_state);
			return -EPROTO;
		}
		add_cl_req = (struct hbm_add_client_request *)mei_msg;
		ret = mei_hbm_fw_add_cl_req(dev, add_cl_req);
		if (ret) {
			dev_err(dev->dev, "hbm: add client: failed to send response %d\n",
				ret);
			return -EIO;
		}
		dev_dbg(dev->dev, "hbm: add client request processed\n");
		break;

	case MEI_HBM_NOTIFY_RES_CMD:
		dev_dbg(dev->dev, "hbm: notify response received\n");
		mei_hbm_cl_res(dev, cl_cmd, notify_res_to_fop(cl_cmd));
		break;

	case MEI_HBM_NOTIFICATION_CMD:
		dev_dbg(dev->dev, "hbm: notification\n");
		mei_hbm_cl_notify(dev, cl_cmd);
		break;

	default:
		WARN(1, "hbm: wrong command %d\n", mei_msg->hbm_cmd);
		return -EPROTO;

	}
	return 0;
}