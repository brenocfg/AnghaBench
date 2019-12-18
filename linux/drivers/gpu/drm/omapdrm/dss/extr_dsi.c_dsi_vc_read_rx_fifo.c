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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct dsi_data {scalar_t__ debug_read; } ;
typedef  enum dss_dsi_content_type { ____Placeholder_dss_dsi_content_type } dss_dsi_content_type ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int /*<<< orphan*/  DSI_VC_SHORT_PACKET_HEADER (int) ; 
 int /*<<< orphan*/  DSSDBG (char*,...) ; 
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 int DSS_DSI_CONTENT_GENERIC ; 
 int EIO ; 
 void* FLD_GET (int,int,int) ; 
 scalar_t__ MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT ; 
 scalar_t__ MIPI_DSI_RX_DCS_LONG_READ_RESPONSE ; 
 scalar_t__ MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE ; 
 scalar_t__ MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE ; 
 scalar_t__ MIPI_DSI_RX_GENERIC_LONG_READ_RESPONSE ; 
 scalar_t__ MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_1BYTE ; 
 scalar_t__ MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_2BYTE ; 
 scalar_t__ REG_GET (struct dsi_data*,int /*<<< orphan*/ ,int,int) ; 
 int dsi_read_reg (struct dsi_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_show_rx_ack_with_err (int) ; 

__attribute__((used)) static int dsi_vc_read_rx_fifo(struct dsi_data *dsi, int channel, u8 *buf,
			       int buflen, enum dss_dsi_content_type type)
{
	u32 val;
	u8 dt;
	int r;

	/* RX_FIFO_NOT_EMPTY */
	if (REG_GET(dsi, DSI_VC_CTRL(channel), 20, 20) == 0) {
		DSSERR("RX fifo empty when trying to read.\n");
		r = -EIO;
		goto err;
	}

	val = dsi_read_reg(dsi, DSI_VC_SHORT_PACKET_HEADER(channel));
	if (dsi->debug_read)
		DSSDBG("\theader: %08x\n", val);
	dt = FLD_GET(val, 5, 0);
	if (dt == MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT) {
		u16 err = FLD_GET(val, 23, 8);
		dsi_show_rx_ack_with_err(err);
		r = -EIO;
		goto err;

	} else if (dt == (type == DSS_DSI_CONTENT_GENERIC ?
			MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_1BYTE :
			MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE)) {
		u8 data = FLD_GET(val, 15, 8);
		if (dsi->debug_read)
			DSSDBG("\t%s short response, 1 byte: %02x\n",
				type == DSS_DSI_CONTENT_GENERIC ? "GENERIC" :
				"DCS", data);

		if (buflen < 1) {
			r = -EIO;
			goto err;
		}

		buf[0] = data;

		return 1;
	} else if (dt == (type == DSS_DSI_CONTENT_GENERIC ?
			MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_2BYTE :
			MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE)) {
		u16 data = FLD_GET(val, 23, 8);
		if (dsi->debug_read)
			DSSDBG("\t%s short response, 2 byte: %04x\n",
				type == DSS_DSI_CONTENT_GENERIC ? "GENERIC" :
				"DCS", data);

		if (buflen < 2) {
			r = -EIO;
			goto err;
		}

		buf[0] = data & 0xff;
		buf[1] = (data >> 8) & 0xff;

		return 2;
	} else if (dt == (type == DSS_DSI_CONTENT_GENERIC ?
			MIPI_DSI_RX_GENERIC_LONG_READ_RESPONSE :
			MIPI_DSI_RX_DCS_LONG_READ_RESPONSE)) {
		int w;
		int len = FLD_GET(val, 23, 8);
		if (dsi->debug_read)
			DSSDBG("\t%s long response, len %d\n",
				type == DSS_DSI_CONTENT_GENERIC ? "GENERIC" :
				"DCS", len);

		if (len > buflen) {
			r = -EIO;
			goto err;
		}

		/* two byte checksum ends the packet, not included in len */
		for (w = 0; w < len + 2;) {
			int b;
			val = dsi_read_reg(dsi,
				DSI_VC_SHORT_PACKET_HEADER(channel));
			if (dsi->debug_read)
				DSSDBG("\t\t%02x %02x %02x %02x\n",
						(val >> 0) & 0xff,
						(val >> 8) & 0xff,
						(val >> 16) & 0xff,
						(val >> 24) & 0xff);

			for (b = 0; b < 4; ++b) {
				if (w < len)
					buf[w] = (val >> (b * 8)) & 0xff;
				/* we discard the 2 byte checksum */
				++w;
			}
		}

		return len;
	} else {
		DSSERR("\tunknown datatype 0x%02x\n", dt);
		r = -EIO;
		goto err;
	}

err:
	DSSERR("dsi_vc_read_rx_fifo(ch %d type %s) failed\n", channel,
		type == DSS_DSI_CONTENT_GENERIC ? "GENERIC" : "DCS");

	return r;
}