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
struct mtd_info {int dummy; } ;
struct erase_info {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPDDR2_NVM_ERASE ; 
 int lpddr2_nvm_do_block_op (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpddr2_nvm_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	return lpddr2_nvm_do_block_op(mtd, instr->addr, instr->len,
				      LPDDR2_NVM_ERASE);
}