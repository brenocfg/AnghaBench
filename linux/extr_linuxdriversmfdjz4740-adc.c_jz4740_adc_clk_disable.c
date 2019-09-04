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
struct jz4740_adc {int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_ref; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void jz4740_adc_clk_disable(struct jz4740_adc *adc)
{
	if (atomic_dec_return(&adc->clk_ref) == 0)
		clk_disable_unprepare(adc->clk);
}