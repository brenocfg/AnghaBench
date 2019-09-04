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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct tegra_i2c_dev {size_t msg_buf_remaining; int /*<<< orphan*/ * msg_buf; TYPE_1__* hw; } ;
struct TYPE_2__ {scalar_t__ has_mst_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t BYTES_PER_FIFO_WORD ; 
 int /*<<< orphan*/  I2C_FIFO_STATUS ; 
 int I2C_FIFO_STATUS_RX_MASK ; 
 int I2C_FIFO_STATUS_RX_SHIFT ; 
 int /*<<< orphan*/  I2C_MST_FIFO_STATUS ; 
 int I2C_MST_FIFO_STATUS_RX_MASK ; 
 int I2C_MST_FIFO_STATUS_RX_SHIFT ; 
 int /*<<< orphan*/  I2C_RX_FIFO ; 
 int cpu_to_le32 (int) ; 
 int i2c_readl (struct tegra_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_readsl (struct tegra_i2c_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,size_t) ; 

__attribute__((used)) static int tegra_i2c_empty_rx_fifo(struct tegra_i2c_dev *i2c_dev)
{
	u32 val;
	int rx_fifo_avail;
	u8 *buf = i2c_dev->msg_buf;
	size_t buf_remaining = i2c_dev->msg_buf_remaining;
	int words_to_transfer;

	if (i2c_dev->hw->has_mst_fifo) {
		val = i2c_readl(i2c_dev, I2C_MST_FIFO_STATUS);
		rx_fifo_avail = (val & I2C_MST_FIFO_STATUS_RX_MASK) >>
			I2C_MST_FIFO_STATUS_RX_SHIFT;
	} else {
		val = i2c_readl(i2c_dev, I2C_FIFO_STATUS);
		rx_fifo_avail = (val & I2C_FIFO_STATUS_RX_MASK) >>
			I2C_FIFO_STATUS_RX_SHIFT;
	}

	/* Rounds down to not include partial word at the end of buf */
	words_to_transfer = buf_remaining / BYTES_PER_FIFO_WORD;
	if (words_to_transfer > rx_fifo_avail)
		words_to_transfer = rx_fifo_avail;

	i2c_readsl(i2c_dev, buf, I2C_RX_FIFO, words_to_transfer);

	buf += words_to_transfer * BYTES_PER_FIFO_WORD;
	buf_remaining -= words_to_transfer * BYTES_PER_FIFO_WORD;
	rx_fifo_avail -= words_to_transfer;

	/*
	 * If there is a partial word at the end of buf, handle it manually to
	 * prevent overwriting past the end of buf
	 */
	if (rx_fifo_avail > 0 && buf_remaining > 0) {
		BUG_ON(buf_remaining > 3);
		val = i2c_readl(i2c_dev, I2C_RX_FIFO);
		val = cpu_to_le32(val);
		memcpy(buf, &val, buf_remaining);
		buf_remaining = 0;
		rx_fifo_avail--;
	}

	BUG_ON(rx_fifo_avail > 0 && buf_remaining > 0);
	i2c_dev->msg_buf_remaining = buf_remaining;
	i2c_dev->msg_buf = buf;

	return 0;
}