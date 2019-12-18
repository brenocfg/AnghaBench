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
struct dm_clone_region_hydration {unsigned long region_nr; int /*<<< orphan*/  h; int /*<<< orphan*/  list; scalar_t__ status; int /*<<< orphan*/  deferred_bios; int /*<<< orphan*/ * overwrite_bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hydration_init(struct dm_clone_region_hydration *hd, unsigned long region_nr)
{
	hd->region_nr = region_nr;
	hd->overwrite_bio = NULL;
	bio_list_init(&hd->deferred_bios);
	hd->status = 0;

	INIT_LIST_HEAD(&hd->list);
	INIT_HLIST_NODE(&hd->h);
}