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
struct TYPE_2__ {scalar_t__ rb_right; scalar_t__ rb_left; } ;
struct drbd_interval {scalar_t__ sector; int size; TYPE_1__ rb; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ interval_end (scalar_t__) ; 

__attribute__((used)) static inline sector_t
compute_subtree_last(struct drbd_interval *node)
{
	sector_t max = node->sector + (node->size >> 9);

	if (node->rb.rb_left) {
		sector_t left = interval_end(node->rb.rb_left);
		if (left > max)
			max = left;
	}
	if (node->rb.rb_right) {
		sector_t right = interval_end(node->rb.rb_right);
		if (right > max)
			max = right;
	}
	return max;
}