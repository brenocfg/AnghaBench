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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_10__ {scalar_t__ status; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct wired_cmd_close_session_out {TYPE_5__ header; TYPE_2__ member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  physical_port; int /*<<< orphan*/  integrated_port_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  buffer_len; scalar_t__ status; int /*<<< orphan*/  command_id; int /*<<< orphan*/  api_version; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct wired_cmd_close_session_in {TYPE_4__ port; TYPE_3__ header; TYPE_1__ member_0; } ;
struct mei_cl_device {int dummy; } ;
struct hdcp_port_data {int /*<<< orphan*/  port; int /*<<< orphan*/  port_type; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  session_close_out ;
typedef  int /*<<< orphan*/  session_close_in ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  HDCP_API_VERSION ; 
 scalar_t__ ME_HDCP_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WIRED_CLOSE_SESSION ; 
 int /*<<< orphan*/  WIRED_CMD_BUF_LEN_CLOSE_SESSION_IN ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__) ; 
 scalar_t__ mei_cldev_recv (struct mei_cl_device*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mei_cldev_send (struct mei_cl_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mei_get_ddi_index (int /*<<< orphan*/ ) ; 
 struct mei_cl_device* to_mei_cl_device (struct device*) ; 

__attribute__((used)) static int
mei_hdcp_close_session(struct device *dev, struct hdcp_port_data *data)
{
	struct wired_cmd_close_session_in session_close_in = { { 0 } };
	struct wired_cmd_close_session_out session_close_out = { { 0 } };
	struct mei_cl_device *cldev;
	ssize_t byte;

	if (!dev || !data)
		return -EINVAL;

	cldev = to_mei_cl_device(dev);

	session_close_in.header.api_version = HDCP_API_VERSION;
	session_close_in.header.command_id = WIRED_CLOSE_SESSION;
	session_close_in.header.status = ME_HDCP_STATUS_SUCCESS;
	session_close_in.header.buffer_len =
				WIRED_CMD_BUF_LEN_CLOSE_SESSION_IN;

	session_close_in.port.integrated_port_type = data->port_type;
	session_close_in.port.physical_port = mei_get_ddi_index(data->port);

	byte = mei_cldev_send(cldev, (u8 *)&session_close_in,
			      sizeof(session_close_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		return byte;
	}

	byte = mei_cldev_recv(cldev, (u8 *)&session_close_out,
			      sizeof(session_close_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		return byte;
	}

	if (session_close_out.header.status != ME_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "Session Close Failed. status: 0x%X\n",
			session_close_out.header.status);
		return -EIO;
	}

	return 0;
}