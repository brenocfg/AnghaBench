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
struct TYPE_4__ {int /*<<< orphan*/  poll; } ;
struct TYPE_3__ {scalar_t__ polling; int /*<<< orphan*/  holdoff_tmr; } ;
struct sge_qset {TYPE_2__ napi; TYPE_1__ rspq; } ;
struct qset_params {int coalesce_usecs; scalar_t__ polling; } ;

/* Variables and functions */
 int /*<<< orphan*/  max (int,unsigned int) ; 
 int /*<<< orphan*/  napi_rx_handler ; 
 int /*<<< orphan*/  ofld_poll ; 

void t3_update_qset_coalesce(struct sge_qset *qs, const struct qset_params *p)
{
	qs->rspq.holdoff_tmr = max(p->coalesce_usecs * 10, 1U);/* can't be 0 */
	qs->rspq.polling = p->polling;
	qs->napi.poll = p->polling ? napi_rx_handler : ofld_poll;
}