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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_CKGR_MCFR ; 
 unsigned int AT91_PMC_MAINF ; 
 unsigned int AT91_PMC_MAINRDY ; 
 unsigned int MAINF_DIV ; 
 unsigned int SLOW_CLOCK_FREQ ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned long clk_main_recalc_rate(struct regmap *regmap,
					  unsigned long parent_rate)
{
	unsigned int mcfr;

	if (parent_rate)
		return parent_rate;

	pr_warn("Main crystal frequency not set, using approximate value\n");
	regmap_read(regmap, AT91_CKGR_MCFR, &mcfr);
	if (!(mcfr & AT91_PMC_MAINRDY))
		return 0;

	return ((mcfr & AT91_PMC_MAINF) * SLOW_CLOCK_FREQ) / MAINF_DIV;
}