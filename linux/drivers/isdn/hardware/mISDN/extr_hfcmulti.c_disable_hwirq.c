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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  r_irq_ctrl; } ;
struct hfc_multi {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFC_outb (struct hfc_multi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_IRQ_CTRL ; 
 scalar_t__ V_GLOB_IRQ_EN ; 

__attribute__((used)) static void
disable_hwirq(struct hfc_multi *hc)
{
	hc->hw.r_irq_ctrl &= ~((u_char)V_GLOB_IRQ_EN);
	HFC_outb(hc, R_IRQ_CTRL, hc->hw.r_irq_ctrl);
}