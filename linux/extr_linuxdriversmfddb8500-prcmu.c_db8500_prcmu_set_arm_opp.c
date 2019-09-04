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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__ header; scalar_t__ arm_opp; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__ ack; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 scalar_t__ APE_NO_CHANGE ; 
 scalar_t__ ARM_EXTCLK ; 
 scalar_t__ ARM_NO_CHANGE ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ MB1H_ARM_APE_OPP ; 
 int MBOX_BIT (int) ; 
 int /*<<< orphan*/  PRCM_MBOX_CPU_SET ; 
 int /*<<< orphan*/  PRCM_MBOX_CPU_VAL ; 
 scalar_t__ PRCM_MBOX_HEADER_REQ_MB1 ; 
 scalar_t__ PRCM_REQ_MB1_APE_OPP ; 
 scalar_t__ PRCM_REQ_MB1_ARM_OPP ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_2__ mb1_transfer ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

int db8500_prcmu_set_arm_opp(u8 opp)
{
	int r;

	if (opp < ARM_NO_CHANGE || opp > ARM_EXTCLK)
		return -EINVAL;

	r = 0;

	mutex_lock(&mb1_transfer.lock);

	while (readl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(1))
		cpu_relax();

	writeb(MB1H_ARM_APE_OPP, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB1));
	writeb(opp, (tcdm_base + PRCM_REQ_MB1_ARM_OPP));
	writeb(APE_NO_CHANGE, (tcdm_base + PRCM_REQ_MB1_APE_OPP));

	writel(MBOX_BIT(1), PRCM_MBOX_CPU_SET);
	wait_for_completion(&mb1_transfer.work);

	if ((mb1_transfer.ack.header != MB1H_ARM_APE_OPP) ||
		(mb1_transfer.ack.arm_opp != opp))
		r = -EIO;

	mutex_unlock(&mb1_transfer.lock);

	return r;
}