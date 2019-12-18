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
struct badblocks {scalar_t__ count; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  badblocks_check (struct badblocks*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static inline bool is_bad_pmem(struct badblocks *bb, sector_t sector,
		unsigned int len)
{
	if (bb->count) {
		sector_t first_bad;
		int num_bad;

		return !!badblocks_check(bb, sector, len / 512, &first_bad,
				&num_bad);
	}

	return false;
}