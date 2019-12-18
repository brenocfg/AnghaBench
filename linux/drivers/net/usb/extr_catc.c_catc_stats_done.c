#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct ctrl_queue {int index; scalar_t__ buf; } ;
struct catc {char* stats_buf; int* stats_vals; TYPE_2__* netdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  collisions; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int EthStats ; 
#define  RxFramErr 131 
#define  TxExcessColl 130 
#define  TxMultiColl 129 
#define  TxSingleColl 128 

__attribute__((used)) static void catc_stats_done(struct catc *catc, struct ctrl_queue *q)
{
	int index = q->index - EthStats;
	u16 data, last;

	catc->stats_buf[index] = *((char *)q->buf);

	if (index & 1)
		return;

	data = ((u16)catc->stats_buf[index] << 8) | catc->stats_buf[index + 1];
	last = catc->stats_vals[index >> 1];

	switch (index) {
		case TxSingleColl:
		case TxMultiColl:
			catc->netdev->stats.collisions += data - last;
			break;
		case TxExcessColl:
			catc->netdev->stats.tx_aborted_errors += data - last;
			catc->netdev->stats.tx_errors += data - last;
			break;
		case RxFramErr:
			catc->netdev->stats.rx_frame_errors += data - last;
			catc->netdev->stats.rx_errors += data - last;
			break;
	}

	catc->stats_vals[index >> 1] = data;
}