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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int /*<<< orphan*/  rb_left; int /*<<< orphan*/  rb_right; } ;
struct memtype {scalar_t__ end; TYPE_1__ rb; } ;

/* Variables and functions */
 scalar_t__ get_subtree_max_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 compute_subtree_max_end(struct memtype *data)
{
	u64 max_end = data->end, child_max_end;

	child_max_end = get_subtree_max_end(data->rb.rb_right);
	if (child_max_end > max_end)
		max_end = child_max_end;

	child_max_end = get_subtree_max_end(data->rb.rb_left);
	if (child_max_end > max_end)
		max_end = child_max_end;

	return max_end;
}