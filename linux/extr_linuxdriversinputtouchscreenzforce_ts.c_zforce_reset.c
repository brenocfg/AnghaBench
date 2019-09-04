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
struct zforce_ts {int /*<<< orphan*/  reg_vdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  zforce_reset_assert (struct zforce_ts*) ; 

__attribute__((used)) static void zforce_reset(void *data)
{
	struct zforce_ts *ts = data;

	zforce_reset_assert(ts);

	udelay(10);

	if (!IS_ERR(ts->reg_vdd))
		regulator_disable(ts->reg_vdd);
}