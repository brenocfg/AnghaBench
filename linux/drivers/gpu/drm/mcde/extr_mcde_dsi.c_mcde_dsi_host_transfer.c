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
typedef  size_t u32 ;
struct mipi_dsi_msg {int* tx_buf; size_t tx_len; size_t rx_len; size_t type; int* rx_buf; int /*<<< orphan*/  channel; } ;
struct mipi_dsi_host {int dummy; } ;
struct mcde_dsi {scalar_t__ regs; int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ DSI_CMD_MODE_STS_CLR ; 
 scalar_t__ DSI_DIRECT_CMD_MAIN_SETTINGS ; 
 size_t DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_HEAD_SHIFT ; 
 size_t DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_ID_SHIFT ; 
 size_t DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_LONGNOTSHORT ; 
 size_t DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_LP_EN ; 
 size_t DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_NAT_READ ; 
 size_t DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_NAT_WRITE ; 
 size_t DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_SIZE_SHIFT ; 
 scalar_t__ DSI_DIRECT_CMD_RDDAT ; 
 scalar_t__ DSI_DIRECT_CMD_RD_INIT ; 
 scalar_t__ DSI_DIRECT_CMD_RD_PROPERTY ; 
 size_t DSI_DIRECT_CMD_RD_PROPERTY_RD_SIZE_MASK ; 
 scalar_t__ DSI_DIRECT_CMD_SEND ; 
 scalar_t__ DSI_DIRECT_CMD_STS ; 
 size_t DSI_DIRECT_CMD_STS_ACKNOWLEDGE_WITH_ERR_RECEIVED ; 
 size_t DSI_DIRECT_CMD_STS_ACK_VAL_SHIFT ; 
 scalar_t__ DSI_DIRECT_CMD_STS_CLR ; 
 size_t DSI_DIRECT_CMD_STS_READ_COMPLETED ; 
 size_t DSI_DIRECT_CMD_STS_READ_COMPLETED_WITH_ERR ; 
 size_t DSI_DIRECT_CMD_STS_WRITE_COMPLETED ; 
 scalar_t__ DSI_DIRECT_CMD_WRDAT0 ; 
 scalar_t__ DSI_DIRECT_CMD_WRDAT1 ; 
 scalar_t__ DSI_DIRECT_CMD_WRDAT2 ; 
 scalar_t__ DSI_DIRECT_CMD_WRDAT3 ; 
 int EIO ; 
 int ETIME ; 
 scalar_t__ MCDE_DSI_HOST_IS_READ (size_t) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct mcde_dsi* host_to_mcde_dsi (struct mipi_dsi_host*) ; 
 scalar_t__ mipi_dsi_packet_format_is_long (size_t) ; 
 size_t readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (size_t const,size_t const) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static ssize_t mcde_dsi_host_transfer(struct mipi_dsi_host *host,
				      const struct mipi_dsi_msg *msg)
{
	struct mcde_dsi *d = host_to_mcde_dsi(host);
	const u32 loop_delay_us = 10; /* us */
	const u8 *tx = msg->tx_buf;
	u32 loop_counter;
	size_t txlen = msg->tx_len;
	size_t rxlen = msg->rx_len;
	u32 val;
	int ret;
	int i;

	if (txlen > 16) {
		dev_err(d->dev,
			"dunno how to write more than 16 bytes yet\n");
		return -EIO;
	}
	if (rxlen > 4) {
		dev_err(d->dev,
			"dunno how to read more than 4 bytes yet\n");
		return -EIO;
	}

	dev_dbg(d->dev,
		"message to channel %d, write %zd bytes read %zd bytes\n",
		msg->channel, txlen, rxlen);

	/* Command "nature" */
	if (MCDE_DSI_HOST_IS_READ(msg->type))
		/* MCTL_MAIN_DATA_CTL already set up */
		val = DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_NAT_READ;
	else
		val = DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_NAT_WRITE;
	/*
	 * More than 2 bytes will not fit in a single packet, so it's
	 * time to set the "long not short" bit. One byte is used by
	 * the MIPI DCS command leaving just one byte for the payload
	 * in a short package.
	 */
	if (mipi_dsi_packet_format_is_long(msg->type))
		val |= DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_LONGNOTSHORT;
	val |= 0 << DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_ID_SHIFT;
	val |= txlen << DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_SIZE_SHIFT;
	val |= DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_LP_EN;
	val |= msg->type << DSI_DIRECT_CMD_MAIN_SETTINGS_CMD_HEAD_SHIFT;
	writel(val, d->regs + DSI_DIRECT_CMD_MAIN_SETTINGS);

	/* MIPI DCS command is part of the data */
	if (txlen > 0) {
		val = 0;
		for (i = 0; i < 4 && i < txlen; i++)
			val |= tx[i] << (i & 3) * 8;
	}
	writel(val, d->regs + DSI_DIRECT_CMD_WRDAT0);
	if (txlen > 4) {
		val = 0;
		for (i = 0; i < 4 && (i + 4) < txlen; i++)
			val |= tx[i + 4] << (i & 3) * 8;
		writel(val, d->regs + DSI_DIRECT_CMD_WRDAT1);
	}
	if (txlen > 8) {
		val = 0;
		for (i = 0; i < 4 && (i + 8) < txlen; i++)
			val |= tx[i + 8] << (i & 3) * 8;
		writel(val, d->regs + DSI_DIRECT_CMD_WRDAT2);
	}
	if (txlen > 12) {
		val = 0;
		for (i = 0; i < 4 && (i + 12) < txlen; i++)
			val |= tx[i + 12] << (i & 3) * 8;
		writel(val, d->regs + DSI_DIRECT_CMD_WRDAT3);
	}

	writel(~0, d->regs + DSI_DIRECT_CMD_STS_CLR);
	writel(~0, d->regs + DSI_CMD_MODE_STS_CLR);
	/* Send command */
	writel(1, d->regs + DSI_DIRECT_CMD_SEND);

	loop_counter = 1000 * 1000 / loop_delay_us;
	if (MCDE_DSI_HOST_IS_READ(msg->type)) {
		/* Read command */
		while (!(readl(d->regs + DSI_DIRECT_CMD_STS) &
			 (DSI_DIRECT_CMD_STS_READ_COMPLETED |
			  DSI_DIRECT_CMD_STS_READ_COMPLETED_WITH_ERR))
		       && --loop_counter)
			usleep_range(loop_delay_us, (loop_delay_us * 3) / 2);
		if (!loop_counter) {
			dev_err(d->dev, "DSI read timeout!\n");
			return -ETIME;
		}
	} else {
		/* Writing only */
		while (!(readl(d->regs + DSI_DIRECT_CMD_STS) &
			 DSI_DIRECT_CMD_STS_WRITE_COMPLETED)
		       && --loop_counter)
			usleep_range(loop_delay_us, (loop_delay_us * 3) / 2);

		if (!loop_counter) {
			dev_err(d->dev, "DSI write timeout!\n");
			return -ETIME;
		}
	}

	val = readl(d->regs + DSI_DIRECT_CMD_STS);
	if (val & DSI_DIRECT_CMD_STS_READ_COMPLETED_WITH_ERR) {
		dev_err(d->dev, "read completed with error\n");
		writel(1, d->regs + DSI_DIRECT_CMD_RD_INIT);
		return -EIO;
	}
	if (val & DSI_DIRECT_CMD_STS_ACKNOWLEDGE_WITH_ERR_RECEIVED) {
		val >>= DSI_DIRECT_CMD_STS_ACK_VAL_SHIFT;
		dev_err(d->dev, "error during transmission: %04x\n",
			val);
		return -EIO;
	}

	if (!MCDE_DSI_HOST_IS_READ(msg->type)) {
		/* Return number of bytes written */
		ret = txlen;
	} else {
		/* OK this is a read command, get the response */
		u32 rdsz;
		u32 rddat;
		u8 *rx = msg->rx_buf;

		rdsz = readl(d->regs + DSI_DIRECT_CMD_RD_PROPERTY);
		rdsz &= DSI_DIRECT_CMD_RD_PROPERTY_RD_SIZE_MASK;
		rddat = readl(d->regs + DSI_DIRECT_CMD_RDDAT);
		if (rdsz < rxlen) {
			dev_err(d->dev, "read error, requested %zd got %d\n",
				rxlen, rdsz);
			return -EIO;
		}
		/* FIXME: read more than 4 bytes */
		for (i = 0; i < 4 && i < rxlen; i++)
			rx[i] = (rddat >> (i * 8)) & 0xff;
		ret = rdsz;
	}

	writel(~0, d->regs + DSI_DIRECT_CMD_STS_CLR);
	writel(~0, d->regs + DSI_CMD_MODE_STS_CLR);

	return ret;
}