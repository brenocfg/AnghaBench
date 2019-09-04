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
struct imx_timer {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ V2_TSTAT ; 
 int /*<<< orphan*/  V2_TSTAT_OF1 ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void imx31_gpt_irq_acknowledge(struct imx_timer *imxtm)
{
	writel_relaxed(V2_TSTAT_OF1, imxtm->base + V2_TSTAT);
}