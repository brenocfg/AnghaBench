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
typedef  int /*<<< orphan*/  u64 ;
struct qede_rx_queue {int dummy; } ;
struct TYPE_2__ {int offset; } ;

/* Variables and functions */
 int QEDE_NUM_RQSTATS ; 
 TYPE_1__* qede_rqstats_arr ; 

__attribute__((used)) static void qede_get_ethtool_stats_rxq(struct qede_rx_queue *rxq, u64 **buf)
{
	int i;

	for (i = 0; i < QEDE_NUM_RQSTATS; i++) {
		**buf = *((u64 *)(((void *)rxq) + qede_rqstats_arr[i].offset));
		(*buf)++;
	}
}