#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  verify_repeater_out ;
typedef  int /*<<< orphan*/  verify_repeater_in ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_10__ {scalar_t__ status; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct wired_cmd_verify_repeater_out {int /*<<< orphan*/  v; TYPE_5__ header; TYPE_2__ member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  physical_port; int /*<<< orphan*/  integrated_port_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  buffer_len; scalar_t__ status; int /*<<< orphan*/  command_id; int /*<<< orphan*/  api_version; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct wired_cmd_verify_repeater_in {int /*<<< orphan*/  receiver_ids; int /*<<< orphan*/  v_prime; int /*<<< orphan*/  seq_num_v; int /*<<< orphan*/  rx_info; TYPE_4__ port; TYPE_3__ header; TYPE_1__ member_0; } ;
struct mei_cl_device {int dummy; } ;
struct hdcp_port_data {int /*<<< orphan*/  port; int /*<<< orphan*/  port_type; } ;
struct hdcp2_rep_send_receiverid_list {int /*<<< orphan*/  receiver_ids; int /*<<< orphan*/  v_prime; int /*<<< orphan*/  seq_num_v; int /*<<< orphan*/  rx_info; } ;
struct hdcp2_rep_send_ack {int /*<<< orphan*/  msg_id; int /*<<< orphan*/  v; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  HDCP_2_2_RECEIVER_IDS_MAX_LEN ; 
 int /*<<< orphan*/  HDCP_2_2_REP_SEND_ACK ; 
 int /*<<< orphan*/  HDCP_2_2_RXINFO_LEN ; 
 int /*<<< orphan*/  HDCP_2_2_SEQ_NUM_LEN ; 
 int /*<<< orphan*/  HDCP_2_2_V_PRIME_HALF_LEN ; 
 int /*<<< orphan*/  HDCP_API_VERSION ; 
 scalar_t__ ME_HDCP_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WIRED_CMD_BUF_LEN_VERIFY_REPEATER_IN ; 
 int /*<<< orphan*/  WIRED_VERIFY_REPEATER ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,...) ; 
 scalar_t__ mei_cldev_recv (struct mei_cl_device*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mei_cldev_send (struct mei_cl_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mei_get_ddi_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mei_cl_device* to_mei_cl_device (struct device*) ; 

__attribute__((used)) static int
mei_hdcp_repeater_check_flow_prepare_ack(struct device *dev,
					 struct hdcp_port_data *data,
					 struct hdcp2_rep_send_receiverid_list
							*rep_topology,
					 struct hdcp2_rep_send_ack
							*rep_send_ack)
{
	struct wired_cmd_verify_repeater_in verify_repeater_in = { { 0 } };
	struct wired_cmd_verify_repeater_out verify_repeater_out = { { 0 } };
	struct mei_cl_device *cldev;
	ssize_t byte;

	if (!dev || !rep_topology || !rep_send_ack || !data)
		return -EINVAL;

	cldev = to_mei_cl_device(dev);

	verify_repeater_in.header.api_version = HDCP_API_VERSION;
	verify_repeater_in.header.command_id = WIRED_VERIFY_REPEATER;
	verify_repeater_in.header.status = ME_HDCP_STATUS_SUCCESS;
	verify_repeater_in.header.buffer_len =
					WIRED_CMD_BUF_LEN_VERIFY_REPEATER_IN;

	verify_repeater_in.port.integrated_port_type = data->port_type;
	verify_repeater_in.port.physical_port = mei_get_ddi_index(data->port);

	memcpy(verify_repeater_in.rx_info, rep_topology->rx_info,
	       HDCP_2_2_RXINFO_LEN);
	memcpy(verify_repeater_in.seq_num_v, rep_topology->seq_num_v,
	       HDCP_2_2_SEQ_NUM_LEN);
	memcpy(verify_repeater_in.v_prime, rep_topology->v_prime,
	       HDCP_2_2_V_PRIME_HALF_LEN);
	memcpy(verify_repeater_in.receiver_ids, rep_topology->receiver_ids,
	       HDCP_2_2_RECEIVER_IDS_MAX_LEN);

	byte = mei_cldev_send(cldev, (u8 *)&verify_repeater_in,
			      sizeof(verify_repeater_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		return byte;
	}

	byte = mei_cldev_recv(cldev, (u8 *)&verify_repeater_out,
			      sizeof(verify_repeater_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		return byte;
	}

	if (verify_repeater_out.header.status != ME_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X failed. status: 0x%X\n",
			WIRED_VERIFY_REPEATER,
			verify_repeater_out.header.status);
		return -EIO;
	}

	memcpy(rep_send_ack->v, verify_repeater_out.v,
	       HDCP_2_2_V_PRIME_HALF_LEN);
	rep_send_ack->msg_id = HDCP_2_2_REP_SEND_ACK;

	return 0;
}