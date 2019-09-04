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
struct bset_sort_state {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 

void bch_bset_sort_state_free(struct bset_sort_state *state)
{
	mempool_exit(&state->pool);
}