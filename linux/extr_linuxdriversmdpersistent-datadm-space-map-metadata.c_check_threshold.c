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
struct threshold {int value_set; int /*<<< orphan*/  current_value; int /*<<< orphan*/  context; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 scalar_t__ below_threshold (struct threshold*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  threshold_already_triggered (struct threshold*) ; 

__attribute__((used)) static void check_threshold(struct threshold *t, dm_block_t value)
{
	if (below_threshold(t, value) &&
	    !threshold_already_triggered(t))
		t->fn(t->context);

	t->value_set = true;
	t->current_value = value;
}