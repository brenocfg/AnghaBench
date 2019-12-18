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

/* Variables and functions */
 int /*<<< orphan*/  AT (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int NFP_CPP_ACTION_RW ; 
 int NFP_CPP_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P32 ; 
 int /*<<< orphan*/  P64 ; 

__attribute__((used)) static int nfp6000_mu_common(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(NFP_CPP_ACTION_RW, 0, P64, P64);	/* read_be/write_be */
	AT(NFP_CPP_ACTION_RW, 1, P64, P64);	/* read_le/write_le */
	AT(NFP_CPP_ACTION_RW, 2, P64, P64);	/* read_swap_be/write_swap_be */
	AT(NFP_CPP_ACTION_RW, 3, P64, P64);	/* read_swap_le/write_swap_le */
	AT(0, 0,   0, P64);	/* read_be */
	AT(0, 1,   0, P64);	/* read_le */
	AT(0, 2,   0, P64);	/* read_swap_be */
	AT(0, 3,   0, P64);	/* read_swap_le */
	AT(1, 0, P64,   0);	/* write_be */
	AT(1, 1, P64,   0);	/* write_le */
	AT(1, 2, P64,   0);	/* write_swap_be */
	AT(1, 3, P64,   0);	/* write_swap_le */
	AT(3, 0,   0, P32);	/* atomic_read */
	AT(3, 2, P32,   0);	/* mask_compare_write */
	AT(4, 0, P32,   0);	/* atomic_write */
	AT(4, 2,   0,   0);	/* atomic_write_imm */
	AT(4, 3,   0, P32);	/* swap_imm */
	AT(5, 0, P32,   0);	/* set */
	AT(5, 3,   0, P32);	/* test_set_imm */
	AT(6, 0, P32,   0);	/* clr */
	AT(6, 3,   0, P32);	/* test_clr_imm */
	AT(7, 0, P32,   0);	/* add */
	AT(7, 3,   0, P32);	/* test_add_imm */
	AT(8, 0, P32,   0);	/* addsat */
	AT(8, 3,   0, P32);	/* test_subsat_imm */
	AT(9, 0, P32,   0);	/* sub */
	AT(9, 3,   0, P32);	/* test_sub_imm */
	AT(10, 0, P32,   0);	/* subsat */
	AT(10, 3,   0, P32);	/* test_subsat_imm */
	AT(13, 0,   0, P32);	/* microq128_get */
	AT(13, 1,   0, P32);	/* microq128_pop */
	AT(13, 2, P32,   0);	/* microq128_put */
	AT(15, 0, P32,   0);	/* xor */
	AT(15, 3,   0, P32);	/* test_xor_imm */
	AT(28, 0,   0, P32);	/* read32_be */
	AT(28, 1,   0, P32);	/* read32_le */
	AT(28, 2,   0, P32);	/* read32_swap_be */
	AT(28, 3,   0, P32);	/* read32_swap_le */
	AT(31, 0, P32,   0);	/* write32_be */
	AT(31, 1, P32,   0);	/* write32_le */
	AT(31, 2, P32,   0);	/* write32_swap_be */
	AT(31, 3, P32,   0);	/* write32_swap_le */
	default:
		return -EINVAL;
	}
}