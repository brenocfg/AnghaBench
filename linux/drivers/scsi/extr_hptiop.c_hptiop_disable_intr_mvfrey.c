#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* mu; } ;
struct TYPE_6__ {TYPE_2__ mvfrey; } ;
struct hptiop_hba {TYPE_3__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  pcie_f0_int_enable; int /*<<< orphan*/  isr_enable; int /*<<< orphan*/  f0_doorbell_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hptiop_disable_intr_mvfrey(struct hptiop_hba *hba)
{
	writel(0, &(hba->u.mvfrey.mu->f0_doorbell_enable));
	readl(&(hba->u.mvfrey.mu->f0_doorbell_enable));
	writel(0, &(hba->u.mvfrey.mu->isr_enable));
	readl(&(hba->u.mvfrey.mu->isr_enable));
	writel(0, &(hba->u.mvfrey.mu->pcie_f0_int_enable));
	readl(&(hba->u.mvfrey.mu->pcie_f0_int_enable));
}