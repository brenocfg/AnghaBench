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
typedef  int u32 ;
typedef  int u16 ;
struct exynos_dsi_transfer {int* rx_payload; int rx_done; int rx_len; scalar_t__ result; } ;
struct exynos_dsi {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSIM_RXFIFO_REG ; 
 int DSI_RX_FIFO_EMPTY ; 
 int DSI_RX_FIFO_SIZE ; 
#define  MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT 132 
#define  MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE 131 
#define  MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE 130 
#define  MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_1BYTE 129 
#define  MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_2BYTE 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int exynos_dsi_read (struct exynos_dsi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_dsi_read_from_fifo(struct exynos_dsi *dsi,
					struct exynos_dsi_transfer *xfer)
{
	u8 *payload = xfer->rx_payload + xfer->rx_done;
	bool first = !xfer->rx_done;
	struct device *dev = dsi->dev;
	u16 length;
	u32 reg;

	if (first) {
		reg = exynos_dsi_read(dsi, DSIM_RXFIFO_REG);

		switch (reg & 0x3f) {
		case MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_2BYTE:
		case MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE:
			if (xfer->rx_len >= 2) {
				payload[1] = reg >> 16;
				++xfer->rx_done;
			}
			/* Fall through */
		case MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_1BYTE:
		case MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE:
			payload[0] = reg >> 8;
			++xfer->rx_done;
			xfer->rx_len = xfer->rx_done;
			xfer->result = 0;
			goto clear_fifo;
		case MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT:
			dev_err(dev, "DSI Error Report: 0x%04x\n",
				(reg >> 8) & 0xffff);
			xfer->result = 0;
			goto clear_fifo;
		}

		length = (reg >> 8) & 0xffff;
		if (length > xfer->rx_len) {
			dev_err(dev,
				"response too long (%u > %u bytes), stripping\n",
				xfer->rx_len, length);
			length = xfer->rx_len;
		} else if (length < xfer->rx_len)
			xfer->rx_len = length;
	}

	length = xfer->rx_len - xfer->rx_done;
	xfer->rx_done += length;

	/* Receive payload */
	while (length >= 4) {
		reg = exynos_dsi_read(dsi, DSIM_RXFIFO_REG);
		payload[0] = (reg >>  0) & 0xff;
		payload[1] = (reg >>  8) & 0xff;
		payload[2] = (reg >> 16) & 0xff;
		payload[3] = (reg >> 24) & 0xff;
		payload += 4;
		length -= 4;
	}

	if (length) {
		reg = exynos_dsi_read(dsi, DSIM_RXFIFO_REG);
		switch (length) {
		case 3:
			payload[2] = (reg >> 16) & 0xff;
			/* Fall through */
		case 2:
			payload[1] = (reg >> 8) & 0xff;
			/* Fall through */
		case 1:
			payload[0] = reg & 0xff;
		}
	}

	if (xfer->rx_done == xfer->rx_len)
		xfer->result = 0;

clear_fifo:
	length = DSI_RX_FIFO_SIZE / 4;
	do {
		reg = exynos_dsi_read(dsi, DSIM_RXFIFO_REG);
		if (reg == DSI_RX_FIFO_EMPTY)
			break;
	} while (--length);
}