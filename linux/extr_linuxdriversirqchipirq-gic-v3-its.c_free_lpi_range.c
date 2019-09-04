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
typedef  int /*<<< orphan*/  u32 ;
struct lpi_range {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_sort (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpi_range_cmp ; 
 int /*<<< orphan*/  lpi_range_list ; 
 int /*<<< orphan*/  lpi_range_lock ; 
 int /*<<< orphan*/  merge_lpi_ranges () ; 
 struct lpi_range* mk_lpi_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int free_lpi_range(u32 base, u32 nr_lpis)
{
	struct lpi_range *new;
	int err = 0;

	mutex_lock(&lpi_range_lock);

	new = mk_lpi_range(base, nr_lpis);
	if (!new) {
		err = -ENOMEM;
		goto out;
	}

	list_add(&new->entry, &lpi_range_list);
	list_sort(NULL, &lpi_range_list, lpi_range_cmp);
	merge_lpi_ranges();
out:
	mutex_unlock(&lpi_range_lock);
	return err;
}