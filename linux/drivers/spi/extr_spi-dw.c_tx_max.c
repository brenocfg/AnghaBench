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
typedef  int u32 ;
struct dw_spi {int tx_end; int tx; int n_bytes; int fifo_len; int rx_end; int rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_SPI_TXFLR ; 
 int dw_readl (struct dw_spi*,int /*<<< orphan*/ ) ; 
 int min3 (int,int,int) ; 

__attribute__((used)) static inline u32 tx_max(struct dw_spi *dws)
{
	u32 tx_left, tx_room, rxtx_gap;

	tx_left = (dws->tx_end - dws->tx) / dws->n_bytes;
	tx_room = dws->fifo_len - dw_readl(dws, DW_SPI_TXFLR);

	/*
	 * Another concern is about the tx/rx mismatch, we
	 * though to use (dws->fifo_len - rxflr - txflr) as
	 * one maximum value for tx, but it doesn't cover the
	 * data which is out of tx/rx fifo and inside the
	 * shift registers. So a control from sw point of
	 * view is taken.
	 */
	rxtx_gap =  ((dws->rx_end - dws->rx) - (dws->tx_end - dws->tx))
			/ dws->n_bytes;

	return min3(tx_left, tx_room, (u32) (dws->fifo_len - rxtx_gap));
}