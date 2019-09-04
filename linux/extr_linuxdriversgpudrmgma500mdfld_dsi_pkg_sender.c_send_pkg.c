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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mdfld_dsi_pkg_sender {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EAGAIN ; 
 scalar_t__ MDFLD_DSI_PKG_SENDER_BUSY ; 
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
 int dsi_error_handler (struct mdfld_dsi_pkg_sender*) ; 
 int send_long_pkg (struct mdfld_dsi_pkg_sender*,int,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_pkg_done (struct mdfld_dsi_pkg_sender*,int,int*,int /*<<< orphan*/ ) ; 
 int send_pkg_prepare (struct mdfld_dsi_pkg_sender*,int,int*,int /*<<< orphan*/ ) ; 
 int send_short_pkg (struct mdfld_dsi_pkg_sender*,int,int,int,int) ; 

__attribute__((used)) static int send_pkg(struct mdfld_dsi_pkg_sender *sender, u8 data_type,
		u8 *data, u16 len, bool hs)
{
	int ret;

	/*handle DSI error*/
	ret = dsi_error_handler(sender);
	if (ret) {
		DRM_ERROR("Error handling failed\n");
		return -EAGAIN;
	}

	/* send pkg */
	if (sender->status == MDFLD_DSI_PKG_SENDER_BUSY) {
		DRM_ERROR("sender is busy\n");
		return -EAGAIN;
	}

	ret = send_pkg_prepare(sender, data_type, data, len);
	if (ret) {
		DRM_ERROR("send_pkg_prepare error\n");
		return ret;
	}

	switch (data_type) {
	case MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM:
	case MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM:
	case MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM:
	case MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM:
	case MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM:
	case MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM:
	case MIPI_DSI_DCS_SHORT_WRITE:
	case MIPI_DSI_DCS_SHORT_WRITE_PARAM:
	case MIPI_DSI_DCS_READ:
		ret = send_short_pkg(sender, data_type, data[0], data[1], hs);
		break;
	case MIPI_DSI_GENERIC_LONG_WRITE:
	case MIPI_DSI_DCS_LONG_WRITE:
		ret = send_long_pkg(sender, data_type, data, len, hs);
		break;
	}

	send_pkg_done(sender, data_type, data, len);

	/*FIXME: should I query complete and fifo empty here?*/

	return ret;
}