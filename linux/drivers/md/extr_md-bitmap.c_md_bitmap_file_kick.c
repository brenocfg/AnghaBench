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
struct TYPE_2__ {scalar_t__ file; } ;
struct bitmap {TYPE_1__ storage; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_STALE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bmname (struct bitmap*) ; 
 char* file_path (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_bitmap_update_sb (struct bitmap*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void md_bitmap_file_kick(struct bitmap *bitmap)
{
	char *path, *ptr = NULL;

	if (!test_and_set_bit(BITMAP_STALE, &bitmap->flags)) {
		md_bitmap_update_sb(bitmap);

		if (bitmap->storage.file) {
			path = kmalloc(PAGE_SIZE, GFP_KERNEL);
			if (path)
				ptr = file_path(bitmap->storage.file,
					     path, PAGE_SIZE);

			pr_warn("%s: kicking failed bitmap file %s from array!\n",
				bmname(bitmap), IS_ERR(ptr) ? "" : ptr);

			kfree(path);
		} else
			pr_warn("%s: disabling internal bitmap due to errors\n",
				bmname(bitmap));
	}
}