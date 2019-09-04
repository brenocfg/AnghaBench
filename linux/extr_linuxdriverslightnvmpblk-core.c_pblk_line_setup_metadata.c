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
struct pblk_line_mgmt {TYPE_1__** eline_meta; int /*<<< orphan*/ * sline_meta; int /*<<< orphan*/  meta_bitmap; int /*<<< orphan*/  free_lock; } ;
struct pblk_line_meta {int /*<<< orphan*/ * emeta_len; int /*<<< orphan*/  smeta_len; } ;
struct pblk_line {int meta_line; TYPE_1__* emeta; int /*<<< orphan*/  smeta; } ;
struct TYPE_2__ {int /*<<< orphan*/  sync; scalar_t__ mem; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int PBLK_DATA_LINES ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pblk_line_setup_metadata(struct pblk_line *line,
				     struct pblk_line_mgmt *l_mg,
				     struct pblk_line_meta *lm)
{
	int meta_line;

	lockdep_assert_held(&l_mg->free_lock);

retry_meta:
	meta_line = find_first_zero_bit(&l_mg->meta_bitmap, PBLK_DATA_LINES);
	if (meta_line == PBLK_DATA_LINES) {
		spin_unlock(&l_mg->free_lock);
		io_schedule();
		spin_lock(&l_mg->free_lock);
		goto retry_meta;
	}

	set_bit(meta_line, &l_mg->meta_bitmap);
	line->meta_line = meta_line;

	line->smeta = l_mg->sline_meta[meta_line];
	line->emeta = l_mg->eline_meta[meta_line];

	memset(line->smeta, 0, lm->smeta_len);
	memset(line->emeta->buf, 0, lm->emeta_len[0]);

	line->emeta->mem = 0;
	atomic_set(&line->emeta->sync, 0);
}