#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  blk; } ;
struct ppa_addr {TYPE_2__ a; } ;
struct pblk_line_meta {int blk_per_line; } ;
struct pblk_line {int /*<<< orphan*/  id; int /*<<< orphan*/  lock; int /*<<< orphan*/  erase_bitmap; int /*<<< orphan*/  left_eblks; } ;
struct pblk {TYPE_1__* luns; struct pblk_line_meta lm; } ;
struct TYPE_3__ {struct ppa_addr bppa; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 int pblk_blk_erase_sync (struct pblk*,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 

int pblk_line_erase(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_meta *lm = &pblk->lm;
	struct ppa_addr ppa;
	int ret, bit = -1;

	/* Erase only good blocks, one at a time */
	do {
		spin_lock(&line->lock);
		bit = find_next_zero_bit(line->erase_bitmap, lm->blk_per_line,
								bit + 1);
		if (bit >= lm->blk_per_line) {
			spin_unlock(&line->lock);
			break;
		}

		ppa = pblk->luns[bit].bppa; /* set ch and lun */
		ppa.a.blk = line->id;

		atomic_dec(&line->left_eblks);
		WARN_ON(test_and_set_bit(bit, line->erase_bitmap));
		spin_unlock(&line->lock);

		ret = pblk_blk_erase_sync(pblk, ppa);
		if (ret) {
			pblk_err(pblk, "failed to erase line %d\n", line->id);
			return ret;
		}
	} while (1);

	return 0;
}