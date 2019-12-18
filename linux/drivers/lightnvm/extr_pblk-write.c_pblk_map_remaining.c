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
typedef  size_t u64 ;
struct ppa_addr {int dummy; } ;
struct pblk_line {int /*<<< orphan*/  lock; TYPE_2__* w_err_gc; int /*<<< orphan*/  vsc; int /*<<< orphan*/  invalid_bitmap; int /*<<< orphan*/  nr_valid_lbas; int /*<<< orphan*/  left_msecs; int /*<<< orphan*/  map_bitmap; TYPE_1__* emeta; } ;
struct pblk {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ __le64 ;
struct TYPE_4__ {int has_write_err; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EMPTY ; 
 scalar_t__ cpu_to_le64 (int /*<<< orphan*/ ) ; 
 scalar_t__* emeta_to_lbas (struct pblk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ ,int) ; 
 int nvm_next_ppa_in_chk (int /*<<< orphan*/ ,struct ppa_addr*) ; 
 size_t pblk_dev_ppa_to_line_addr (struct pblk*,struct ppa_addr) ; 
 struct pblk_line* pblk_ppa_to_line (struct pblk*,struct ppa_addr) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pblk_map_remaining(struct pblk *pblk, struct ppa_addr *ppa,
		int rqd_ppas)
{
	struct pblk_line *line;
	struct ppa_addr map_ppa = *ppa;
	__le64 addr_empty = cpu_to_le64(ADDR_EMPTY);
	__le64 *lba_list;
	u64 paddr;
	int done = 0;
	int n = 0;

	line = pblk_ppa_to_line(pblk, *ppa);
	lba_list = emeta_to_lbas(pblk, line->emeta->buf);

	spin_lock(&line->lock);

	while (!done)  {
		paddr = pblk_dev_ppa_to_line_addr(pblk, map_ppa);

		if (!test_and_set_bit(paddr, line->map_bitmap))
			line->left_msecs--;

		if (n < rqd_ppas && lba_list[paddr] != addr_empty)
			line->nr_valid_lbas--;

		lba_list[paddr] = addr_empty;

		if (!test_and_set_bit(paddr, line->invalid_bitmap))
			le32_add_cpu(line->vsc, -1);

		done = nvm_next_ppa_in_chk(pblk->dev, &map_ppa);

		n++;
	}

	line->w_err_gc->has_write_err = 1;
	spin_unlock(&line->lock);
}