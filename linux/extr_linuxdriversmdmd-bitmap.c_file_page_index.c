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
struct bitmap_storage {scalar_t__ sb_page; } ;
typedef  int /*<<< orphan*/  bitmap_super_t ;

/* Variables and functions */
 unsigned long PAGE_BIT_SHIFT ; 

__attribute__((used)) static inline unsigned long file_page_index(struct bitmap_storage *store,
					    unsigned long chunk)
{
	if (store->sb_page)
		chunk += sizeof(bitmap_super_t) << 3;
	return chunk >> PAGE_BIT_SHIFT;
}