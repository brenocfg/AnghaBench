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
struct reg_addr {int size; int addr; int /*<<< orphan*/  presets; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_REG_IN_PRESET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int const,int const) ; 
 int* __bnx2x_get_page_addr_ar (struct bnx2x*) ; 
 struct reg_addr* __bnx2x_get_page_read_ar (struct bnx2x*) ; 
 int __bnx2x_get_page_read_num (struct bnx2x*) ; 
 int __bnx2x_get_page_reg_num (struct bnx2x*) ; 
 int* __bnx2x_get_page_write_ar (struct bnx2x*) ; 
 int __bnx2x_get_page_write_num (struct bnx2x*) ; 

__attribute__((used)) static void bnx2x_read_pages_regs(struct bnx2x *bp, u32 *p, u32 preset)
{
	u32 i, j, k, n;

	/* addresses of the paged registers */
	const u32 *page_addr = __bnx2x_get_page_addr_ar(bp);
	/* number of paged registers */
	int num_pages = __bnx2x_get_page_reg_num(bp);
	/* write addresses */
	const u32 *write_addr = __bnx2x_get_page_write_ar(bp);
	/* number of write addresses */
	int write_num = __bnx2x_get_page_write_num(bp);
	/* read addresses info */
	const struct reg_addr *read_addr = __bnx2x_get_page_read_ar(bp);
	/* number of read addresses */
	int read_num = __bnx2x_get_page_read_num(bp);
	u32 addr, size;

	for (i = 0; i < num_pages; i++) {
		for (j = 0; j < write_num; j++) {
			REG_WR(bp, write_addr[j], page_addr[i]);

			for (k = 0; k < read_num; k++) {
				if (IS_REG_IN_PRESET(read_addr[k].presets,
						     preset)) {
					size = read_addr[k].size;
					for (n = 0; n < size; n++) {
						addr = read_addr[k].addr + n*4;
						*p++ = REG_RD(bp, addr);
					}
				}
			}
		}
	}
}