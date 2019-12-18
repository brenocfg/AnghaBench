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
struct tx_servq {scalar_t__ qcnt; int /*<<< orphan*/  sta_pending; int /*<<< orphan*/  tx_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_init_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _init_txservq(struct tx_servq *ptxservq)
{
	INIT_LIST_HEAD(&ptxservq->tx_pending);
	_rtw_init_queue(&ptxservq->sta_pending);
	ptxservq->qcnt = 0;
}