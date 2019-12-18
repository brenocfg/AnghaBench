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
struct threshold {scalar_t__ threshold; scalar_t__ threshold_set; } ;
typedef  scalar_t__ dm_block_t ;

/* Variables and functions */

__attribute__((used)) static bool below_threshold(struct threshold *t, dm_block_t value)
{
	return t->threshold_set && value <= t->threshold;
}