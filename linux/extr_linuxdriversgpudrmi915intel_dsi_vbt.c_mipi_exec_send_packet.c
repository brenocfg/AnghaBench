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
typedef  int u8 ;
typedef  int u16 ;
struct mipi_dsi_device {int channel; int /*<<< orphan*/  mode_flags; } ;
struct intel_dsi {int ports; TYPE_1__** dsi_hosts; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_2__ {struct mipi_dsi_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
#define  MIPI_DSI_DCS_LONG_WRITE 138 
#define  MIPI_DSI_DCS_READ 137 
#define  MIPI_DSI_DCS_SHORT_WRITE 136 
#define  MIPI_DSI_DCS_SHORT_WRITE_PARAM 135 
#define  MIPI_DSI_GENERIC_LONG_WRITE 134 
#define  MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM 133 
#define  MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM 132 
#define  MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM 131 
#define  MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM 130 
#define  MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM 129 
#define  MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM 128 
 int /*<<< orphan*/  MIPI_DSI_MODE_LPM ; 
 int MIPI_PORT_SHIFT ; 
 int MIPI_TRANSFER_MODE_SHIFT ; 
 int MIPI_VIRTUAL_CHANNEL_SHIFT ; 
 int PORT_C ; 
 int intel_dsi_seq_port_to_port (int) ; 
 int /*<<< orphan*/  mipi_dsi_dcs_write_buffer (struct mipi_dsi_device*,int const*,int) ; 
 int /*<<< orphan*/  mipi_dsi_generic_write (struct mipi_dsi_device*,int const*,int) ; 
 int /*<<< orphan*/  port_name (int) ; 
 int /*<<< orphan*/  vlv_dsi_wait_for_fifo_empty (struct intel_dsi*,int) ; 

__attribute__((used)) static const u8 *mipi_exec_send_packet(struct intel_dsi *intel_dsi,
				       const u8 *data)
{
	struct mipi_dsi_device *dsi_device;
	u8 type, flags, seq_port;
	u16 len;
	enum port port;

	DRM_DEBUG_KMS("\n");

	flags = *data++;
	type = *data++;

	len = *((u16 *) data);
	data += 2;

	seq_port = (flags >> MIPI_PORT_SHIFT) & 3;

	/* For DSI single link on Port A & C, the seq_port value which is
	 * parsed from Sequence Block#53 of VBT has been set to 0
	 * Now, read/write of packets for the DSI single link on Port A and
	 * Port C will based on the DVO port from VBT block 2.
	 */
	if (intel_dsi->ports == (1 << PORT_C))
		port = PORT_C;
	else
		port = intel_dsi_seq_port_to_port(seq_port);

	dsi_device = intel_dsi->dsi_hosts[port]->device;
	if (!dsi_device) {
		DRM_DEBUG_KMS("no dsi device for port %c\n", port_name(port));
		goto out;
	}

	if ((flags >> MIPI_TRANSFER_MODE_SHIFT) & 1)
		dsi_device->mode_flags &= ~MIPI_DSI_MODE_LPM;
	else
		dsi_device->mode_flags |= MIPI_DSI_MODE_LPM;

	dsi_device->channel = (flags >> MIPI_VIRTUAL_CHANNEL_SHIFT) & 3;

	switch (type) {
	case MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM:
		mipi_dsi_generic_write(dsi_device, NULL, 0);
		break;
	case MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM:
		mipi_dsi_generic_write(dsi_device, data, 1);
		break;
	case MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM:
		mipi_dsi_generic_write(dsi_device, data, 2);
		break;
	case MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM:
	case MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM:
	case MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM:
		DRM_DEBUG_DRIVER("Generic Read not yet implemented or used\n");
		break;
	case MIPI_DSI_GENERIC_LONG_WRITE:
		mipi_dsi_generic_write(dsi_device, data, len);
		break;
	case MIPI_DSI_DCS_SHORT_WRITE:
		mipi_dsi_dcs_write_buffer(dsi_device, data, 1);
		break;
	case MIPI_DSI_DCS_SHORT_WRITE_PARAM:
		mipi_dsi_dcs_write_buffer(dsi_device, data, 2);
		break;
	case MIPI_DSI_DCS_READ:
		DRM_DEBUG_DRIVER("DCS Read not yet implemented or used\n");
		break;
	case MIPI_DSI_DCS_LONG_WRITE:
		mipi_dsi_dcs_write_buffer(dsi_device, data, len);
		break;
	}

	vlv_dsi_wait_for_fifo_empty(intel_dsi, port);

out:
	data += len;

	return data;
}