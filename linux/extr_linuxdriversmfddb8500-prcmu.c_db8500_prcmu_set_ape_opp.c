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
struct TYPE_3__ {scalar_t__ header; scalar_t__ ape_opp; } ;
struct TYPE_4__ {scalar_t__ ape_opp; int /*<<< orphan*/  lock; TYPE_1__ ack; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 scalar_t__ APE_100_OPP ; 
 scalar_t__ APE_50_OPP ; 
 scalar_t__ APE_50_PARTLY_25_OPP ; 
 scalar_t__ ARM_NO_CHANGE ; 
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
 int /*<<< orphan*/  request_even_slower_clocks (int) ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

int db8500_prcmu_set_ape_opp(u8 opp)
{
	int r = 0;

	if (opp == mb1_transfer.ape_opp)
		return 0;

	mutex_lock(&mb1_transfer.lock);

	if (mb1_transfer.ape_opp == APE_50_PARTLY_25_OPP)
		request_even_slower_clocks(false);

	if ((opp != APE_100_OPP) && (mb1_transfer.ape_opp != APE_100_OPP))
		goto skip_message;

	while (readl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(1))
		cpu_relax();

	writeb(MB1H_ARM_APE_OPP, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB1));
	writeb(ARM_NO_CHANGE, (tcdm_base + PRCM_REQ_MB1_ARM_OPP));
	writeb(((opp == APE_50_PARTLY_25_OPP) ? APE_50_OPP : opp),
		(tcdm_base + PRCM_REQ_MB1_APE_OPP));

	writel(MBOX_BIT(1), PRCM_MBOX_CPU_SET);
	wait_for_completion(&mb1_transfer.work);

	if ((mb1_transfer.ack.header != MB1H_ARM_APE_OPP) ||
		(mb1_transfer.ack.ape_opp != opp))
		r = -EIO;

skip_message:
	if ((!r && (opp == APE_50_PARTLY_25_OPP)) ||
		(r && (mb1_transfer.ape_opp == APE_50_PARTLY_25_OPP)))
		request_even_slower_clocks(true);
	if (!r)
		mb1_transfer.ape_opp = opp;

	mutex_unlock(&mb1_transfer.lock);

	return r;
}