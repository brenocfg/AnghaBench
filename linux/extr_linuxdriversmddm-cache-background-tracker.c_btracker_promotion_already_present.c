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
struct background_tracker {int dummy; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;

/* Variables and functions */
 int /*<<< orphan*/ * __find_pending (struct background_tracker*,int /*<<< orphan*/ ) ; 

bool btracker_promotion_already_present(struct background_tracker *b,
					dm_oblock_t oblock)
{
	return __find_pending(b, oblock) != NULL;
}