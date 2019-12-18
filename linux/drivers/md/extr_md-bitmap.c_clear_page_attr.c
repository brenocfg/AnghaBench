#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  filemap_attr; } ;
struct bitmap {TYPE_1__ storage; } ;
typedef  enum bitmap_page_attr { ____Placeholder_bitmap_page_attr } bitmap_page_attr ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void clear_page_attr(struct bitmap *bitmap, int pnum,
				   enum bitmap_page_attr attr)
{
	clear_bit((pnum<<2) + attr, bitmap->storage.filemap_attr);
}