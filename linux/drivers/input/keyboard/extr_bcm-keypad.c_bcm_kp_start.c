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
struct bcm_kp {int kpior; int imr0_val; int imr1_val; int kpemr; int kpcr; scalar_t__ base; void** last_state; scalar_t__ clk; } ;

/* Variables and functions */
 int KPCR_ENABLE ; 
 scalar_t__ KPCR_OFFSET ; 
 scalar_t__ KPEMR0_OFFSET ; 
 scalar_t__ KPEMR1_OFFSET ; 
 scalar_t__ KPEMR2_OFFSET ; 
 scalar_t__ KPEMR3_OFFSET ; 
 scalar_t__ KPICR0_OFFSET ; 
 scalar_t__ KPICR1_OFFSET ; 
 scalar_t__ KPIMR0_OFFSET ; 
 scalar_t__ KPIMR1_OFFSET ; 
 scalar_t__ KPIOR_OFFSET ; 
 scalar_t__ KPSSR0_OFFSET ; 
 scalar_t__ KPSSR1_OFFSET ; 
 int clk_prepare_enable (scalar_t__) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int bcm_kp_start(struct bcm_kp *kp)
{
	int error;

	if (kp->clk) {
		error = clk_prepare_enable(kp->clk);
		if (error)
			return error;
	}

	writel(kp->kpior, kp->base + KPIOR_OFFSET);

	writel(kp->imr0_val, kp->base + KPIMR0_OFFSET);
	writel(kp->imr1_val, kp->base + KPIMR1_OFFSET);

	writel(kp->kpemr, kp->base + KPEMR0_OFFSET);
	writel(kp->kpemr, kp->base + KPEMR1_OFFSET);
	writel(kp->kpemr, kp->base + KPEMR2_OFFSET);
	writel(kp->kpemr, kp->base + KPEMR3_OFFSET);

	writel(0xFFFFFFFF, kp->base + KPICR0_OFFSET);
	writel(0xFFFFFFFF, kp->base + KPICR1_OFFSET);

	kp->last_state[0] = readl(kp->base + KPSSR0_OFFSET);
	kp->last_state[0] = readl(kp->base + KPSSR1_OFFSET);

	writel(kp->kpcr | KPCR_ENABLE, kp->base + KPCR_OFFSET);

	return 0;
}