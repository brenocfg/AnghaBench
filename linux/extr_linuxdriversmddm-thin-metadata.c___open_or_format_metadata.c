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
struct dm_pool_metadata {int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int EPERM ; 
 int __format_metadata (struct dm_pool_metadata*) ; 
 int __open_metadata (struct dm_pool_metadata*) ; 
 int __superblock_all_zeroes (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int __open_or_format_metadata(struct dm_pool_metadata *pmd, bool format_device)
{
	int r, unformatted;

	r = __superblock_all_zeroes(pmd->bm, &unformatted);
	if (r)
		return r;

	if (unformatted)
		return format_device ? __format_metadata(pmd) : -EPERM;

	return __open_metadata(pmd);
}