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
typedef  size_t u8 ;
struct rsi_common {TYPE_2__* tx_qinfo; TYPE_1__* edca_params; } ;
struct TYPE_4__ {scalar_t__ pkt_contended; scalar_t__ wme_params; scalar_t__ weight; } ;
struct TYPE_3__ {int cw_min; int aifs; } ;

/* Variables and functions */
 size_t NUM_EDCA_QUEUES ; 
 scalar_t__ SIFS_DURATION ; 
 int WMM_SHORT_SLOT_TIME ; 

__attribute__((used)) static void rsi_set_contention_vals(struct rsi_common *common)
{
	u8 ii = 0;

	for (; ii < NUM_EDCA_QUEUES; ii++) {
		common->tx_qinfo[ii].wme_params =
			(((common->edca_params[ii].cw_min / 2) +
			  (common->edca_params[ii].aifs)) *
			  WMM_SHORT_SLOT_TIME + SIFS_DURATION);
		common->tx_qinfo[ii].weight = common->tx_qinfo[ii].wme_params;
		common->tx_qinfo[ii].pkt_contended = 0;
	}
}