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
 unsigned int AT91_PMC_MAINRDY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MAINFRDY_TIMEOUT ; 
 int /*<<< orphan*/  MAINF_LOOP_MAX_WAIT ; 
 int /*<<< orphan*/  MAINF_LOOP_MIN_WAIT ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_main_probe_frequency(struct regmap *regmap)
{
	unsigned long prep_time, timeout;
	unsigned int mcfr;

	timeout = jiffies + usecs_to_jiffies(MAINFRDY_TIMEOUT);
	do {
		prep_time = jiffies;
		regmap_read(regmap, AT91_CKGR_MCFR, &mcfr);
		if (mcfr & AT91_PMC_MAINRDY)
			return 0;
		usleep_range(MAINF_LOOP_MIN_WAIT, MAINF_LOOP_MAX_WAIT);
	} while (time_before(prep_time, timeout));

	return -ETIMEDOUT;
}