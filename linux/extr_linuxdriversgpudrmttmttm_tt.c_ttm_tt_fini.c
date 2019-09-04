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
struct ttm_tt {int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

void ttm_tt_fini(struct ttm_tt *ttm)
{
	kvfree(ttm->pages);
	ttm->pages = NULL;
}