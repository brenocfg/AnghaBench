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
struct TYPE_3__ {int valid; } ;
struct tx_ts_record {int add_ba_req_in_progress; int add_ba_req_delayed; TYPE_1__ tx_pending_ba_record; } ;
struct timer_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 struct tx_ts_record* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct tx_ts_record* pTxTs ; 
 TYPE_2__ tx_pending_ba_record ; 

void BaSetupTimeOut(struct timer_list *t)
{
	struct tx_ts_record *pTxTs = from_timer(pTxTs, t, tx_pending_ba_record.timer);

	pTxTs->add_ba_req_in_progress = false;
	pTxTs->add_ba_req_delayed = true;
	pTxTs->tx_pending_ba_record.valid = false;
}