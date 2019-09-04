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
typedef  int /*<<< orphan*/  u_char ;
struct nand_chip {int /*<<< orphan*/  IO_ADDR_R; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static u_char au_read_byte16(struct mtd_info *mtd)
{
	struct nand_chip *this = mtd_to_nand(mtd);
	u_char ret = (u_char) cpu_to_le16(readw(this->IO_ADDR_R));
	wmb(); /* drain writebuffer */
	return ret;
}