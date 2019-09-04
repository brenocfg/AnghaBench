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
struct ttm_tt {int /*<<< orphan*/  num_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_pool_unpopulate_helper (struct ttm_tt*,int /*<<< orphan*/ ) ; 

void ttm_pool_unpopulate(struct ttm_tt *ttm)
{
	ttm_pool_unpopulate_helper(ttm, ttm->num_pages);
}