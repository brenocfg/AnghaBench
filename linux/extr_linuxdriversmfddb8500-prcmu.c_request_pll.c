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
struct TYPE_3__ {scalar_t__ header; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__ ack; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ MB1H_PLL_ON_OFF ; 
 int MBOX_BIT (int) ; 
 scalar_t__ PLL_SOC0_OFF ; 
 scalar_t__ PLL_SOC0_ON ; 
 scalar_t__ PLL_SOC1_OFF ; 
 scalar_t__ PLL_SOC1_ON ; 
 scalar_t__ PRCMU_PLLSOC0 ; 
 scalar_t__ PRCMU_PLLSOC1 ; 
 int /*<<< orphan*/  PRCM_MBOX_CPU_SET ; 
 int /*<<< orphan*/  PRCM_MBOX_CPU_VAL ; 
 scalar_t__ PRCM_MBOX_HEADER_REQ_MB1 ; 
 scalar_t__ PRCM_REQ_MB1_PLL_ON_OFF ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_2__ mb1_transfer ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_pll(u8 clock, bool enable)
{
	int r = 0;

	if (clock == PRCMU_PLLSOC0)
		clock = (enable ? PLL_SOC0_ON : PLL_SOC0_OFF);
	else if (clock == PRCMU_PLLSOC1)
		clock = (enable ? PLL_SOC1_ON : PLL_SOC1_OFF);
	else
		return -EINVAL;

	mutex_lock(&mb1_transfer.lock);

	while (readl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(1))
		cpu_relax();

	writeb(MB1H_PLL_ON_OFF, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB1));
	writeb(clock, (tcdm_base + PRCM_REQ_MB1_PLL_ON_OFF));

	writel(MBOX_BIT(1), PRCM_MBOX_CPU_SET);
	wait_for_completion(&mb1_transfer.work);

	if (mb1_transfer.ack.header != MB1H_PLL_ON_OFF)
		r = -EIO;

	mutex_unlock(&mb1_transfer.lock);

	return r;
}