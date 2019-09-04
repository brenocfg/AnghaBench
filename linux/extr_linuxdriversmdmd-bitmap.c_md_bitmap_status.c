#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct bitmap_counts {int pages; int missing_pages; } ;
struct TYPE_6__ {scalar_t__ file; } ;
struct bitmap {TYPE_3__ storage; TYPE_2__* mddev; struct bitmap_counts counts; } ;
struct TYPE_4__ {int chunksize; } ;
struct TYPE_5__ {TYPE_1__ bitmap_info; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  seq_file_path (struct seq_file*,scalar_t__,char*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

void md_bitmap_status(struct seq_file *seq, struct bitmap *bitmap)
{
	unsigned long chunk_kb;
	struct bitmap_counts *counts;

	if (!bitmap)
		return;

	counts = &bitmap->counts;

	chunk_kb = bitmap->mddev->bitmap_info.chunksize >> 10;
	seq_printf(seq, "bitmap: %lu/%lu pages [%luKB], "
		   "%lu%s chunk",
		   counts->pages - counts->missing_pages,
		   counts->pages,
		   (counts->pages - counts->missing_pages)
		   << (PAGE_SHIFT - 10),
		   chunk_kb ? chunk_kb : bitmap->mddev->bitmap_info.chunksize,
		   chunk_kb ? "KB" : "B");
	if (bitmap->storage.file) {
		seq_printf(seq, ", file: ");
		seq_file_path(seq, bitmap->storage.file, " \t\n");
	}

	seq_printf(seq, "\n");
}