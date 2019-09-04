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
struct tioca_common {TYPE_1__ ca_common; } ;
struct ia64_sal_retval {scalar_t__ v0; scalar_t__ status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SAL_CALL_NOLOCK (struct ia64_sal_retval,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SN_SAL_IOIF_ERROR_INTERRUPT ; 

__attribute__((used)) static irqreturn_t
tioca_error_intr_handler(int irq, void *arg)
{
	struct tioca_common *soft = arg;
	struct ia64_sal_retval ret_stuff;
	u64 segment;
	u64 busnum;
	ret_stuff.status = 0;
	ret_stuff.v0 = 0;

	segment = soft->ca_common.bs_persist_segment;
	busnum = soft->ca_common.bs_persist_busnum;

	SAL_CALL_NOLOCK(ret_stuff,
			(u64) SN_SAL_IOIF_ERROR_INTERRUPT,
			segment, busnum, 0, 0, 0, 0, 0);

	return IRQ_HANDLED;
}