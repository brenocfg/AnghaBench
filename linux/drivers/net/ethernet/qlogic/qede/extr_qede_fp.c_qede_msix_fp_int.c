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
struct qede_fastpath {int /*<<< orphan*/  napi; int /*<<< orphan*/  sb_info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IGU_INT_DISABLE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_sb_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

irqreturn_t qede_msix_fp_int(int irq, void *fp_cookie)
{
	struct qede_fastpath *fp = fp_cookie;

	qed_sb_ack(fp->sb_info, IGU_INT_DISABLE, 0 /*do not update*/);

	napi_schedule_irqoff(&fp->napi);
	return IRQ_HANDLED;
}