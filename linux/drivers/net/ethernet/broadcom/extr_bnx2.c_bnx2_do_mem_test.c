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
typedef  int /*<<< orphan*/  test_pattern ;
struct bnx2 {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int const bnx2_reg_rd_ind (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_reg_wr_ind (struct bnx2*,int,int const) ; 

__attribute__((used)) static int
bnx2_do_mem_test(struct bnx2 *bp, u32 start, u32 size)
{
	static const u32 test_pattern[] = { 0x00000000, 0xffffffff, 0x55555555,
		0xaaaaaaaa , 0xaa55aa55, 0x55aa55aa };
	int i;

	for (i = 0; i < sizeof(test_pattern) / 4; i++) {
		u32 offset;

		for (offset = 0; offset < size; offset += 4) {

			bnx2_reg_wr_ind(bp, start + offset, test_pattern[i]);

			if (bnx2_reg_rd_ind(bp, start + offset) !=
				test_pattern[i]) {
				return -ENODEV;
			}
		}
	}
	return 0;
}