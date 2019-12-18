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
struct dmz_metadata {int /*<<< orphan*/  nr_mblks; } ;
struct dmz_mblock {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dmz_mblock*) ; 

__attribute__((used)) static void dmz_free_mblock(struct dmz_metadata *zmd, struct dmz_mblock *mblk)
{
	__free_pages(mblk->page, 0);
	kfree(mblk);

	atomic_dec(&zmd->nr_mblks);
}