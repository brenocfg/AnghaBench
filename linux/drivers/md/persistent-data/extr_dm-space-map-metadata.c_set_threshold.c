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
struct threshold {int threshold_set; void* context; int /*<<< orphan*/  fn; int /*<<< orphan*/  threshold; } ;
typedef  int /*<<< orphan*/  dm_sm_threshold_fn ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */

__attribute__((used)) static void set_threshold(struct threshold *t, dm_block_t value,
			  dm_sm_threshold_fn fn, void *context)
{
	t->threshold_set = true;
	t->threshold = value;
	t->fn = fn;
	t->context = context;
}