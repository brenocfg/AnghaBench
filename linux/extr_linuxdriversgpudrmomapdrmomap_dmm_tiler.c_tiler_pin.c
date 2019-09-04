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
struct tiler_block {int /*<<< orphan*/  area; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int fill (int /*<<< orphan*/ *,struct page**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tiler_unpin (struct tiler_block*) ; 

int tiler_pin(struct tiler_block *block, struct page **pages,
		u32 npages, u32 roll, bool wait)
{
	int ret;

	ret = fill(&block->area, pages, npages, roll, wait);

	if (ret)
		tiler_unpin(block);

	return ret;
}