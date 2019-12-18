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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mlxbf_tmfifo {int tx_fifo_size; scalar_t__ tx_base; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLXBF_TMFIFO_RESERVE_RATIO ; 
 scalar_t__ MLXBF_TMFIFO_TX_STS ; 
 int /*<<< orphan*/  MLXBF_TMFIFO_TX_STS__COUNT_MASK ; 
 int VIRTIO_ID_NET ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 

__attribute__((used)) static int mlxbf_tmfifo_get_tx_avail(struct mlxbf_tmfifo *fifo, int vdev_id)
{
	int tx_reserve;
	u32 count;
	u64 sts;

	/* Reserve some room in FIFO for console messages. */
	if (vdev_id == VIRTIO_ID_NET)
		tx_reserve = fifo->tx_fifo_size / MLXBF_TMFIFO_RESERVE_RATIO;
	else
		tx_reserve = 1;

	sts = readq(fifo->tx_base + MLXBF_TMFIFO_TX_STS);
	count = FIELD_GET(MLXBF_TMFIFO_TX_STS__COUNT_MASK, sts);
	return fifo->tx_fifo_size - tx_reserve - count;
}