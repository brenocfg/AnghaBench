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
struct csis_state {int /*<<< orphan*/ * clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int NUM_CSIS_CLOCKS ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5pcsis_clk_put(struct csis_state *state)
{
	int i;

	for (i = 0; i < NUM_CSIS_CLOCKS; i++) {
		if (IS_ERR(state->clock[i]))
			continue;
		clk_unprepare(state->clock[i]);
		clk_put(state->clock[i]);
		state->clock[i] = ERR_PTR(-EINVAL);
	}
}