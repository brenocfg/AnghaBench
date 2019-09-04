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
struct TYPE_2__ {int /*<<< orphan*/  bs_persist_busnum; int /*<<< orphan*/  bs_persist_segment; } ;
struct tioce_common {TYPE_1__ ce_pcibus; } ;
struct ia64_sal_retval {scalar_t__ v0; scalar_t__ status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SAL_CALL_NOLOCK (struct ia64_sal_retval,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SN_SAL_IOIF_ERROR_INTERRUPT ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static irqreturn_t
tioce_error_intr_handler(int irq, void *arg)
{
	struct tioce_common *soft = arg;
	struct ia64_sal_retval ret_stuff;
	ret_stuff.status = 0;
	ret_stuff.v0 = 0;

	SAL_CALL_NOLOCK(ret_stuff, (u64) SN_SAL_IOIF_ERROR_INTERRUPT,
			soft->ce_pcibus.bs_persist_segment,
			soft->ce_pcibus.bs_persist_busnum, 0, 0, 0, 0, 0);

	if (ret_stuff.v0)
		panic("tioce_error_intr_handler:  Fatal TIOCE error");

	return IRQ_HANDLED;
}