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
typedef  int /*<<< orphan*/  u32 ;
struct spear_adc_state {TYPE_1__* adc_base_spear6xx; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ch_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spear_adc_set_ctrl(struct spear_adc_state *st, int n,
			       u32 val)
{
	__raw_writel(val, &st->adc_base_spear6xx->ch_ctrl[n]);
}