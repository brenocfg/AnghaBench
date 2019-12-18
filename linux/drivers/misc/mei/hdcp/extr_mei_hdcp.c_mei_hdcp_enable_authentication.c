#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {scalar_t__ status; } ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
struct wired_cmd_enable_auth_out {TYPE_6__ header; TYPE_2__ member_0; } ;
struct TYPE_10__ {int /*<<< orphan*/  physical_port; int /*<<< orphan*/  integrated_port_type; } ;
struct TYPE_9__ {int /*<<< orphan*/  buffer_len; scalar_t__ status; int /*<<< orphan*/  command_id; int /*<<< orphan*/  api_version; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct wired_cmd_enable_auth_in {int /*<<< orphan*/  stream_type; TYPE_4__ port; TYPE_3__ header; TYPE_1__ member_0; } ;
struct mei_cl_device {int dummy; } ;
struct hdcp_port_data {TYPE_5__* streams; int /*<<< orphan*/  port; int /*<<< orphan*/  port_type; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  enable_auth_out ;
typedef  int /*<<< orphan*/  enable_auth_in ;
struct TYPE_11__ {int /*<<< orphan*/  stream_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  HDCP_API_VERSION ; 
 scalar_t__ ME_HDCP_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WIRED_CMD_BUF_LEN_ENABLE_AUTH_IN ; 
 int /*<<< orphan*/  WIRED_ENABLE_AUTH ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,...) ; 
 scalar_t__ mei_cldev_recv (struct mei_cl_device*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mei_cldev_send (struct mei_cl_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mei_get_ddi_index (int /*<<< orphan*/ ) ; 
 struct mei_cl_device* to_mei_cl_device (struct device*) ; 

__attribute__((used)) static int mei_hdcp_enable_authentication(struct device *dev,
					  struct hdcp_port_data *data)
{
	struct wired_cmd_enable_auth_in enable_auth_in = { { 0 } };
	struct wired_cmd_enable_auth_out enable_auth_out = { { 0 } };
	struct mei_cl_device *cldev;
	ssize_t byte;

	if (!dev || !data)
		return -EINVAL;

	cldev = to_mei_cl_device(dev);

	enable_auth_in.header.api_version = HDCP_API_VERSION;
	enable_auth_in.header.command_id = WIRED_ENABLE_AUTH;
	enable_auth_in.header.status = ME_HDCP_STATUS_SUCCESS;
	enable_auth_in.header.buffer_len = WIRED_CMD_BUF_LEN_ENABLE_AUTH_IN;

	enable_auth_in.port.integrated_port_type = data->port_type;
	enable_auth_in.port.physical_port = mei_get_ddi_index(data->port);
	enable_auth_in.stream_type = data->streams[0].stream_type;

	byte = mei_cldev_send(cldev, (u8 *)&enable_auth_in,
			      sizeof(enable_auth_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		return byte;
	}

	byte = mei_cldev_recv(cldev, (u8 *)&enable_auth_out,
			      sizeof(enable_auth_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		return byte;
	}

	if (enable_auth_out.header.status != ME_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X failed. status: 0x%X\n",
			WIRED_ENABLE_AUTH, enable_auth_out.header.status);
		return -EIO;
	}

	return 0;
}