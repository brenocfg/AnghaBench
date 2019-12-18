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
struct thin_c {int /*<<< orphan*/  pool; } ;
struct remap_info {int /*<<< orphan*/  issue_bios; int /*<<< orphan*/  defer_bios; struct thin_c* tc; } ;
struct dm_bio_prison_cell {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  __remap_and_issue_shared_cell ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 struct bio* bio_list_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cell_visit_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct remap_info*,struct dm_bio_prison_cell*) ; 
 int /*<<< orphan*/  remap_and_issue (struct thin_c*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thin_defer_bio (struct thin_c*,struct bio*) ; 

__attribute__((used)) static void remap_and_issue_shared_cell(struct thin_c *tc,
					struct dm_bio_prison_cell *cell,
					dm_block_t block)
{
	struct bio *bio;
	struct remap_info info;

	info.tc = tc;
	bio_list_init(&info.defer_bios);
	bio_list_init(&info.issue_bios);

	cell_visit_release(tc->pool, __remap_and_issue_shared_cell,
			   &info, cell);

	while ((bio = bio_list_pop(&info.defer_bios)))
		thin_defer_bio(tc, bio);

	while ((bio = bio_list_pop(&info.issue_bios)))
		remap_and_issue(tc, bio, block);
}