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
struct ashmem_range {size_t pgstart; size_t pgend; unsigned int purged; int /*<<< orphan*/  unpinned; struct ashmem_area* asma; } ;
struct ashmem_area {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_add (struct ashmem_range*) ; 
 scalar_t__ range_on_lru (struct ashmem_range*) ; 

__attribute__((used)) static void range_alloc(struct ashmem_area *asma,
			struct ashmem_range *prev_range, unsigned int purged,
			size_t start, size_t end,
			struct ashmem_range **new_range)
{
	struct ashmem_range *range = *new_range;

	*new_range = NULL;
	range->asma = asma;
	range->pgstart = start;
	range->pgend = end;
	range->purged = purged;

	list_add_tail(&range->unpinned, &prev_range->unpinned);

	if (range_on_lru(range))
		lru_add(range);
}