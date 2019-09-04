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
typedef  int /*<<< orphan*/  const u8 ;
struct marvell_nfc {scalar_t__ regs; } ;

/* Variables and functions */
 unsigned int FIFO_DEPTH ; 
 int /*<<< orphan*/  FIFO_REP (unsigned int) ; 
 scalar_t__ NDDB ; 
 int /*<<< orphan*/  iowrite32_rep (scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int round_down (unsigned int,unsigned int) ; 

__attribute__((used)) static int marvell_nfc_xfer_data_out_pio(struct marvell_nfc *nfc, const u8 *out,
					 unsigned int len)
{
	unsigned int last_len = len % FIFO_DEPTH;
	unsigned int last_full_offset = round_down(len, FIFO_DEPTH);
	int i;

	for (i = 0; i < last_full_offset; i += FIFO_DEPTH)
		iowrite32_rep(nfc->regs + NDDB, out + i, FIFO_REP(FIFO_DEPTH));

	if (last_len) {
		u8 tmp_buf[FIFO_DEPTH];

		memcpy(tmp_buf, out + last_full_offset, last_len);
		iowrite32_rep(nfc->regs + NDDB, tmp_buf, FIFO_REP(FIFO_DEPTH));
	}

	return 0;
}