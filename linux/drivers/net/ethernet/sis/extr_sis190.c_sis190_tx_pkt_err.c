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
struct net_device_stats {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_window_errors; } ;

/* Variables and functions */
 int FIFO ; 
 int LINK ; 
 int TABRT ; 
 int TxErrMask ; 
 int WND ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static inline int sis190_tx_pkt_err(u32 status, struct net_device_stats *stats)
{
#define TxErrMask	(WND | TABRT | FIFO | LINK)

	if (!unlikely(status & TxErrMask))
		return 0;

	if (status & WND)
		stats->tx_window_errors++;
	if (status & TABRT)
		stats->tx_aborted_errors++;
	if (status & FIFO)
		stats->tx_fifo_errors++;
	if (status & LINK)
		stats->tx_carrier_errors++;

	stats->tx_errors++;

	return -1;
}