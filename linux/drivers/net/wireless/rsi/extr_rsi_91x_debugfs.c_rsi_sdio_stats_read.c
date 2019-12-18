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
struct seq_file {struct rsi_common* private; } ;
struct rsi_hw {scalar_t__ rsi_dev; } ;
struct rsi_common {struct rsi_hw* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  mgmt_buf_full_counter; int /*<<< orphan*/  buf_semi_full_counter; int /*<<< orphan*/  buf_full_counter; int /*<<< orphan*/  mgmt_buffer_full; int /*<<< orphan*/  semi_buffer_full; int /*<<< orphan*/  buffer_full; int /*<<< orphan*/  total_sdio_unknown_intr; int /*<<< orphan*/  total_sdio_msdu_pending_intr; int /*<<< orphan*/  sdio_int_counter; } ;
struct rsi_91x_sdiodev {TYPE_1__ rx_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsi_sdio_stats_read(struct seq_file *seq, void *data)
{
	struct rsi_common *common = seq->private;
	struct rsi_hw *adapter = common->priv;
	struct rsi_91x_sdiodev *dev =
		(struct rsi_91x_sdiodev *)adapter->rsi_dev;

	seq_printf(seq, "total_sdio_interrupts: %d\n",
		   dev->rx_info.sdio_int_counter);
	seq_printf(seq, "sdio_msdu_pending_intr_count: %d\n",
		   dev->rx_info.total_sdio_msdu_pending_intr);
	seq_printf(seq, "sdio_buff_full_count : %d\n",
		   dev->rx_info.buf_full_counter);
	seq_printf(seq, "sdio_buf_semi_full_count %d\n",
		   dev->rx_info.buf_semi_full_counter);
	seq_printf(seq, "sdio_unknown_intr_count: %d\n",
		   dev->rx_info.total_sdio_unknown_intr);
	/* RX Path Stats */
	seq_printf(seq, "BUFFER FULL STATUS  : %d\n",
		   dev->rx_info.buffer_full);
	seq_printf(seq, "SEMI BUFFER FULL STATUS  : %d\n",
		   dev->rx_info.semi_buffer_full);
	seq_printf(seq, "MGMT BUFFER FULL STATUS  : %d\n",
		   dev->rx_info.mgmt_buffer_full);
	seq_printf(seq, "BUFFER FULL COUNTER  : %d\n",
		   dev->rx_info.buf_full_counter);
	seq_printf(seq, "BUFFER SEMI FULL COUNTER  : %d\n",
		   dev->rx_info.buf_semi_full_counter);
	seq_printf(seq, "MGMT BUFFER FULL COUNTER  : %d\n",
		   dev->rx_info.mgmt_buf_full_counter);

	return 0;
}