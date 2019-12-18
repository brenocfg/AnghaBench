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
struct TYPE_2__ {int /*<<< orphan*/  cur_window; int /*<<< orphan*/  status; } ;
struct whc_qset {int max_burst; TYPE_1__ qh; scalar_t__ reset; } ;
struct whc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QH_STATUS_SEQ_MASK ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

void qset_reset(struct whc *whc, struct whc_qset *qset)
{
	qset->reset = 0;

	qset->qh.status &= ~QH_STATUS_SEQ_MASK;
	qset->qh.cur_window = cpu_to_le32((1 << qset->max_burst) - 1);
}