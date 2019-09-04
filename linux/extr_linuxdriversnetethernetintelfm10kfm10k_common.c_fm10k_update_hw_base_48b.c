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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct fm10k_hw_stat {int /*<<< orphan*/  base_h; scalar_t__ base_l; } ;

/* Variables and functions */

__attribute__((used)) static void fm10k_update_hw_base_48b(struct fm10k_hw_stat *stat, u64 delta)
{
	if (!delta)
		return;

	/* update lower 32 bits */
	delta += stat->base_l;
	stat->base_l = (u32)delta;

	/* update upper 32 bits */
	stat->base_h += (u32)(delta >> 32);
}