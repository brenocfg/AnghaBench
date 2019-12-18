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
struct tcmu_dev {int dbi_thresh; int dbi_max; int /*<<< orphan*/  data_bitmap; int /*<<< orphan*/  data_blocks; } ;
struct tcmu_cmd {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  global_db_count ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int,struct page*) ; 
 struct page* radix_tree_lookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcmu_cmd_set_dbi (struct tcmu_cmd*,int) ; 
 scalar_t__ tcmu_global_max_blocks ; 
 int /*<<< orphan*/  tcmu_unmap_work ; 

__attribute__((used)) static inline bool tcmu_get_empty_block(struct tcmu_dev *udev,
					struct tcmu_cmd *tcmu_cmd)
{
	struct page *page;
	int ret, dbi;

	dbi = find_first_zero_bit(udev->data_bitmap, udev->dbi_thresh);
	if (dbi == udev->dbi_thresh)
		return false;

	page = radix_tree_lookup(&udev->data_blocks, dbi);
	if (!page) {
		if (atomic_add_return(1, &global_db_count) >
				      tcmu_global_max_blocks)
			schedule_delayed_work(&tcmu_unmap_work, 0);

		/* try to get new page from the mm */
		page = alloc_page(GFP_KERNEL);
		if (!page)
			goto err_alloc;

		ret = radix_tree_insert(&udev->data_blocks, dbi, page);
		if (ret)
			goto err_insert;
	}

	if (dbi > udev->dbi_max)
		udev->dbi_max = dbi;

	set_bit(dbi, udev->data_bitmap);
	tcmu_cmd_set_dbi(tcmu_cmd, dbi);

	return true;
err_insert:
	__free_page(page);
err_alloc:
	atomic_dec(&global_db_count);
	return false;
}