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
struct tegra_adma_desc {unsigned int num_periods; unsigned int buf_len; unsigned int period_len; } ;
struct tegra_adma_chan {unsigned int tx_buf_pos; unsigned int tx_buf_count; struct tegra_adma_desc* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMA_CH_XFER_STATUS ; 
 int ADMA_CH_XFER_STATUS_COUNT_MASK ; 
 unsigned int tdma_ch_read (struct tegra_adma_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int tegra_adma_get_residue(struct tegra_adma_chan *tdc)
{
	struct tegra_adma_desc *desc = tdc->desc;
	unsigned int max = ADMA_CH_XFER_STATUS_COUNT_MASK + 1;
	unsigned int pos = tdma_ch_read(tdc, ADMA_CH_XFER_STATUS);
	unsigned int periods_remaining;

	/*
	 * Handle wrap around of buffer count register
	 */
	if (pos < tdc->tx_buf_pos)
		tdc->tx_buf_count += pos + (max - tdc->tx_buf_pos);
	else
		tdc->tx_buf_count += pos - tdc->tx_buf_pos;

	periods_remaining = tdc->tx_buf_count % desc->num_periods;
	tdc->tx_buf_pos = pos;

	return desc->buf_len - (periods_remaining * desc->period_len);
}