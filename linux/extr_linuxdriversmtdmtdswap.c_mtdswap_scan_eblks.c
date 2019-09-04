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
struct swap_eb {int flags; } ;
struct mtdswap_dev {unsigned int eblks; struct swap_eb* eb_data; } ;

/* Variables and functions */
 int EBLOCK_BAD ; 
 unsigned int EBLOCK_IDX_SHIFT ; 
 int EBLOCK_READERR ; 
 unsigned int MTDSWAP_CLEAN ; 
 unsigned int MTDSWAP_DIRTY ; 
 unsigned int MTDSWAP_FAILING ; 
 int MTDSWAP_SCANNED_BAD ; 
#define  MTDSWAP_SCANNED_BITFLIP 130 
#define  MTDSWAP_SCANNED_CLEAN 129 
#define  MTDSWAP_SCANNED_DIRTY 128 
 int /*<<< orphan*/  mtdswap_check_counts (struct mtdswap_dev*) ; 
 int /*<<< orphan*/  mtdswap_rb_add (struct mtdswap_dev*,struct swap_eb*,unsigned int) ; 
 int mtdswap_read_markers (struct mtdswap_dev*,struct swap_eb*) ; 

__attribute__((used)) static void mtdswap_scan_eblks(struct mtdswap_dev *d)
{
	int status;
	unsigned int i, idx;
	struct swap_eb *eb;

	for (i = 0; i < d->eblks; i++) {
		eb = d->eb_data + i;

		status = mtdswap_read_markers(d, eb);
		if (status < 0)
			eb->flags |= EBLOCK_READERR;
		else if (status == MTDSWAP_SCANNED_BAD) {
			eb->flags |= EBLOCK_BAD;
			continue;
		}

		switch (status) {
		case MTDSWAP_SCANNED_CLEAN:
			idx = MTDSWAP_CLEAN;
			break;
		case MTDSWAP_SCANNED_DIRTY:
		case MTDSWAP_SCANNED_BITFLIP:
			idx = MTDSWAP_DIRTY;
			break;
		default:
			idx = MTDSWAP_FAILING;
		}

		eb->flags |= (idx << EBLOCK_IDX_SHIFT);
	}

	mtdswap_check_counts(d);

	for (i = 0; i < d->eblks; i++) {
		eb = d->eb_data + i;

		if (eb->flags & EBLOCK_BAD)
			continue;

		idx = eb->flags >> EBLOCK_IDX_SHIFT;
		mtdswap_rb_add(d, eb, idx);
	}
}