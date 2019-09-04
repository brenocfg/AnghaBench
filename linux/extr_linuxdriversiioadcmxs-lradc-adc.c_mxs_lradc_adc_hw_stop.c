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
struct mxs_lradc_adc {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LRADC_DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxs_lradc_adc_hw_stop(struct mxs_lradc_adc *adc)
{
	writel(0, adc->base + LRADC_DELAY(0));
}