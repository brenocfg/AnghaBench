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
typedef  int u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
#define  AEU_INPUTS_ATTN_BITS_ATC_PARITY_ERROR 129 
#define  AEU_INPUTS_ATTN_BITS_PGLUE_PARITY_ERROR 128 
 int /*<<< orphan*/  ATC_REG_ATC_PRTY_STS ; 
 int /*<<< orphan*/  PGLUE_B_REG_PGLUE_B_PRTY_STS ; 
 int /*<<< orphan*/  _print_next_block (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _print_parity (struct bnx2x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bnx2x_check_blocks_with_parity4(struct bnx2x *bp, u32 sig,
					    int *par_num, bool print)
{
	u32 cur_bit;
	bool res;
	int i;

	res = false;

	for (i = 0; sig; i++) {
		cur_bit = (0x1UL << i);
		if (sig & cur_bit) {
			res = true; /* Each bit is real error! */
			if (print) {
				switch (cur_bit) {
				case AEU_INPUTS_ATTN_BITS_PGLUE_PARITY_ERROR:
					_print_next_block((*par_num)++,
							  "PGLUE_B");
					_print_parity(bp,
						      PGLUE_B_REG_PGLUE_B_PRTY_STS);
					break;
				case AEU_INPUTS_ATTN_BITS_ATC_PARITY_ERROR:
					_print_next_block((*par_num)++, "ATC");
					_print_parity(bp,
						      ATC_REG_ATC_PRTY_STS);
					break;
				}
			}
			/* Clear the bit */
			sig &= ~cur_bit;
		}
	}

	return res;
}