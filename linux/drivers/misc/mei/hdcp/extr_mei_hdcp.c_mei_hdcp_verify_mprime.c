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
typedef  int /*<<< orphan*/  verify_mprime_out ;
typedef  int /*<<< orphan*/  verify_mprime_in ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_10__ {scalar_t__ status; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct wired_cmd_repeater_auth_stream_req_out {TYPE_5__ header; TYPE_2__ member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  physical_port; int /*<<< orphan*/  integrated_port_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  buffer_len; scalar_t__ status; int /*<<< orphan*/  command_id; int /*<<< orphan*/  api_version; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct wired_cmd_repeater_auth_stream_req_in {int /*<<< orphan*/  k; int /*<<< orphan*/  streams; int /*<<< orphan*/  seq_num_m; int /*<<< orphan*/  m_prime; TYPE_4__ port; TYPE_3__ header; TYPE_1__ member_0; } ;
struct mei_cl_device {int dummy; } ;
struct hdcp_port_data {int k; int /*<<< orphan*/  streams; int /*<<< orphan*/  seq_num_m; int /*<<< orphan*/  port; int /*<<< orphan*/  port_type; } ;
struct hdcp2_streamid_type {int dummy; } ;
struct hdcp2_rep_stream_ready {int /*<<< orphan*/  m_prime; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int HDCP_2_2_MPRIME_LEN ; 
 int /*<<< orphan*/  HDCP_API_VERSION ; 
 scalar_t__ ME_HDCP_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WIRED_CMD_BUF_LEN_REPEATER_AUTH_STREAM_REQ_MIN_IN ; 
 int /*<<< orphan*/  WIRED_REPEATER_AUTH_STREAM_REQ ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  drm_hdcp_cpu_to_be24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mei_cldev_recv (struct mei_cl_device*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mei_cldev_send (struct mei_cl_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mei_get_ddi_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mei_cl_device* to_mei_cl_device (struct device*) ; 

__attribute__((used)) static int mei_hdcp_verify_mprime(struct device *dev,
				  struct hdcp_port_data *data,
				  struct hdcp2_rep_stream_ready *stream_ready)
{
	struct wired_cmd_repeater_auth_stream_req_in
					verify_mprime_in = { { 0 } };
	struct wired_cmd_repeater_auth_stream_req_out
					verify_mprime_out = { { 0 } };
	struct mei_cl_device *cldev;
	ssize_t byte;

	if (!dev || !stream_ready || !data)
		return -EINVAL;

	cldev = to_mei_cl_device(dev);

	verify_mprime_in.header.api_version = HDCP_API_VERSION;
	verify_mprime_in.header.command_id = WIRED_REPEATER_AUTH_STREAM_REQ;
	verify_mprime_in.header.status = ME_HDCP_STATUS_SUCCESS;
	verify_mprime_in.header.buffer_len =
			WIRED_CMD_BUF_LEN_REPEATER_AUTH_STREAM_REQ_MIN_IN;

	verify_mprime_in.port.integrated_port_type = data->port_type;
	verify_mprime_in.port.physical_port = mei_get_ddi_index(data->port);

	memcpy(verify_mprime_in.m_prime, stream_ready->m_prime,
	       HDCP_2_2_MPRIME_LEN);
	drm_hdcp_cpu_to_be24(verify_mprime_in.seq_num_m, data->seq_num_m);
	memcpy(verify_mprime_in.streams, data->streams,
	       (data->k * sizeof(struct hdcp2_streamid_type)));

	verify_mprime_in.k = cpu_to_be16(data->k);

	byte = mei_cldev_send(cldev, (u8 *)&verify_mprime_in,
			      sizeof(verify_mprime_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		return byte;
	}

	byte = mei_cldev_recv(cldev, (u8 *)&verify_mprime_out,
			      sizeof(verify_mprime_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		return byte;
	}

	if (verify_mprime_out.header.status != ME_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X failed. status: 0x%X\n",
			WIRED_REPEATER_AUTH_STREAM_REQ,
			verify_mprime_out.header.status);
		return -EIO;
	}

	return 0;
}