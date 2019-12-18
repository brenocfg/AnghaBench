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
struct pblk_line_meta {int min_blk_line; int /*<<< orphan*/  meta_distance; int /*<<< orphan*/  blk_per_line; } ;
struct pblk_line {scalar_t__ state; int /*<<< orphan*/  sec_to_update; int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; int /*<<< orphan*/  meta_distance; int /*<<< orphan*/  left_seblks; int /*<<< orphan*/  left_eblks; int /*<<< orphan*/  id; int /*<<< orphan*/  blk_bitmap; int /*<<< orphan*/  erase_bitmap; int /*<<< orphan*/  blk_in_line; } ;
struct pblk {struct pblk_line_meta lm; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 scalar_t__ PBLK_LINESTATE_FREE ; 
 scalar_t__ PBLK_LINESTATE_NEW ; 
 scalar_t__ PBLK_LINESTATE_OPEN ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bitmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_disk_name (struct pblk*) ; 
 int pblk_prepare_new_line (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_pblk_line_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pblk_line_prepare(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_meta *lm = &pblk->lm;
	int blk_in_line = atomic_read(&line->blk_in_line);
	int blk_to_erase;

	/* Bad blocks do not need to be erased */
	bitmap_copy(line->erase_bitmap, line->blk_bitmap, lm->blk_per_line);

	spin_lock(&line->lock);

	/* If we have not written to this line, we need to mark up free chunks
	 * as already erased
	 */
	if (line->state == PBLK_LINESTATE_NEW) {
		blk_to_erase = pblk_prepare_new_line(pblk, line);
		line->state = PBLK_LINESTATE_FREE;
		trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);
	} else {
		blk_to_erase = blk_in_line;
	}

	if (blk_in_line < lm->min_blk_line) {
		spin_unlock(&line->lock);
		return -EAGAIN;
	}

	if (line->state != PBLK_LINESTATE_FREE) {
		WARN(1, "pblk: corrupted line %d, state %d\n",
							line->id, line->state);
		spin_unlock(&line->lock);
		return -EINTR;
	}

	line->state = PBLK_LINESTATE_OPEN;
	trace_pblk_line_state(pblk_disk_name(pblk), line->id,
				line->state);

	atomic_set(&line->left_eblks, blk_to_erase);
	atomic_set(&line->left_seblks, blk_to_erase);

	line->meta_distance = lm->meta_distance;
	spin_unlock(&line->lock);

	kref_init(&line->ref);
	atomic_set(&line->sec_to_update, 0);

	return 0;
}