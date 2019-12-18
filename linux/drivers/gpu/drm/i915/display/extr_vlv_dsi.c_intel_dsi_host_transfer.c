#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct mipi_dsi_packet {int* header; int* payload; scalar_t__ payload_length; } ;
struct mipi_dsi_msg {int flags; int /*<<< orphan*/  rx_len; int /*<<< orphan*/  rx_buf; } ;
struct mipi_dsi_host {int dummy; } ;
struct intel_dsi_host {int port; TYPE_3__* intel_dsi; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct TYPE_6__ {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int const GEN_READ_DATA_AVAIL ; 
 int HS_CTRL_FIFO_FULL ; 
 int HS_DATA_FIFO_FULL ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int const) ; 
 int LP_CTRL_FIFO_FULL ; 
 int LP_DATA_FIFO_FULL ; 
 int MIPI_DSI_MSG_USE_LPM ; 
 int /*<<< orphan*/  MIPI_GEN_FIFO_STAT (int) ; 
 int /*<<< orphan*/  MIPI_HS_GEN_CTRL (int) ; 
 int /*<<< orphan*/  MIPI_HS_GEN_DATA (int) ; 
 int /*<<< orphan*/  MIPI_INTR_STAT (int) ; 
 int /*<<< orphan*/  MIPI_LP_GEN_CTRL (int) ; 
 int /*<<< orphan*/  MIPI_LP_GEN_DATA (int) ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ mipi_dsi_create_packet (struct mipi_dsi_packet*,struct mipi_dsi_msg const*) ; 
 int /*<<< orphan*/  read_data (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_dsi_host* to_intel_dsi_host (struct mipi_dsi_host*) ; 
 int /*<<< orphan*/  write_data (struct drm_i915_private*,int /*<<< orphan*/ ,int*,scalar_t__) ; 

__attribute__((used)) static ssize_t intel_dsi_host_transfer(struct mipi_dsi_host *host,
				       const struct mipi_dsi_msg *msg)
{
	struct intel_dsi_host *intel_dsi_host = to_intel_dsi_host(host);
	struct drm_device *dev = intel_dsi_host->intel_dsi->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	enum port port = intel_dsi_host->port;
	struct mipi_dsi_packet packet;
	ssize_t ret;
	const u8 *header, *data;
	i915_reg_t data_reg, ctrl_reg;
	u32 data_mask, ctrl_mask;

	ret = mipi_dsi_create_packet(&packet, msg);
	if (ret < 0)
		return ret;

	header = packet.header;
	data = packet.payload;

	if (msg->flags & MIPI_DSI_MSG_USE_LPM) {
		data_reg = MIPI_LP_GEN_DATA(port);
		data_mask = LP_DATA_FIFO_FULL;
		ctrl_reg = MIPI_LP_GEN_CTRL(port);
		ctrl_mask = LP_CTRL_FIFO_FULL;
	} else {
		data_reg = MIPI_HS_GEN_DATA(port);
		data_mask = HS_DATA_FIFO_FULL;
		ctrl_reg = MIPI_HS_GEN_CTRL(port);
		ctrl_mask = HS_CTRL_FIFO_FULL;
	}

	/* note: this is never true for reads */
	if (packet.payload_length) {
		if (intel_de_wait_for_clear(dev_priv, MIPI_GEN_FIFO_STAT(port),
					    data_mask, 50))
			DRM_ERROR("Timeout waiting for HS/LP DATA FIFO !full\n");

		write_data(dev_priv, data_reg, packet.payload,
			   packet.payload_length);
	}

	if (msg->rx_len) {
		I915_WRITE(MIPI_INTR_STAT(port), GEN_READ_DATA_AVAIL);
	}

	if (intel_de_wait_for_clear(dev_priv, MIPI_GEN_FIFO_STAT(port),
				    ctrl_mask, 50)) {
		DRM_ERROR("Timeout waiting for HS/LP CTRL FIFO !full\n");
	}

	I915_WRITE(ctrl_reg, header[2] << 16 | header[1] << 8 | header[0]);

	/* ->rx_len is set only for reads */
	if (msg->rx_len) {
		data_mask = GEN_READ_DATA_AVAIL;
		if (intel_de_wait_for_set(dev_priv, MIPI_INTR_STAT(port),
					  data_mask, 50))
			DRM_ERROR("Timeout waiting for read data.\n");

		read_data(dev_priv, data_reg, msg->rx_buf, msg->rx_len);
	}

	/* XXX: fix for reads and writes */
	return 4 + packet.payload_length;
}