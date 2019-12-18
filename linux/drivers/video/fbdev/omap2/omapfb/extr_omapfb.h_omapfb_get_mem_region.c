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
struct omapfb2_mem_region {int /*<<< orphan*/  lock_count; int /*<<< orphan*/  id; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct omapfb2_mem_region *
omapfb_get_mem_region(struct omapfb2_mem_region *rg)
{
	down_read_nested(&rg->lock, rg->id);
	atomic_inc(&rg->lock_count);
	return rg;
}