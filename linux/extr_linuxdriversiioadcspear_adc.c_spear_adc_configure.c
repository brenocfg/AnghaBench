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
struct spear_adc_state {int /*<<< orphan*/  sampling_freq; TYPE_1__* adc_base_spear6xx; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spear_adc_set_clk (struct spear_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spear_adc_set_ctrl (struct spear_adc_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spear_adc_set_scanrate (struct spear_adc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spear_adc_set_status (struct spear_adc_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spear_adc_configure(struct spear_adc_state *st)
{
	int i;

	/* Reset ADC core */
	spear_adc_set_status(st, 0);
	__raw_writel(0, &st->adc_base_spear6xx->clk);
	for (i = 0; i < 8; i++)
		spear_adc_set_ctrl(st, i, 0);
	spear_adc_set_scanrate(st, 0);

	spear_adc_set_clk(st, st->sampling_freq);

	return 0;
}