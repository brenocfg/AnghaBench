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
struct he_dev {unsigned int cells_per_row; unsigned int cells_per_lbuf; unsigned int r1_startrow; unsigned int bytes_per_row; unsigned int r1_numbuffs; } ;

/* Variables and functions */
 unsigned int ATM_CELL_PAYLOAD ; 
 int /*<<< orphan*/  RCMLBM_BA ; 
 int /*<<< orphan*/  RLBF1_C ; 
 int /*<<< orphan*/  RLBF1_H ; 
 int /*<<< orphan*/  RLBF1_T ; 
 int he_readl (struct he_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  he_writel (struct he_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  he_writel_rcm (struct he_dev*,unsigned int,unsigned int) ; 

__attribute__((used)) static void he_init_rx_lbfp1(struct he_dev *he_dev)
{
	unsigned i, lbm_offset, lbufd_index, lbuf_addr, lbuf_count;
	unsigned lbufs_per_row = he_dev->cells_per_row / he_dev->cells_per_lbuf;
	unsigned lbuf_bufsize = he_dev->cells_per_lbuf * ATM_CELL_PAYLOAD;
	unsigned row_offset = he_dev->r1_startrow * he_dev->bytes_per_row;
	
	lbufd_index = 1;
	lbm_offset = he_readl(he_dev, RCMLBM_BA) + (2 * lbufd_index);

	he_writel(he_dev, lbufd_index, RLBF1_H);

	for (i = 0, lbuf_count = 0; i < he_dev->r1_numbuffs; ++i) {
		lbufd_index += 2;
		lbuf_addr = (row_offset + (lbuf_count * lbuf_bufsize)) / 32;

		he_writel_rcm(he_dev, lbuf_addr, lbm_offset);
		he_writel_rcm(he_dev, lbufd_index, lbm_offset + 1);

		if (++lbuf_count == lbufs_per_row) {
			lbuf_count = 0;
			row_offset += he_dev->bytes_per_row;
		}
		lbm_offset += 4;
	}
		
	he_writel(he_dev, lbufd_index - 2, RLBF1_T);
	he_writel(he_dev, he_dev->r1_numbuffs, RLBF1_C);
}