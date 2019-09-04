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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct nand_chip {int /*<<< orphan*/  IO_ADDR_R; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void docg4_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	int i;
	struct nand_chip *nand = mtd_to_nand(mtd);
	uint16_t *p = (uint16_t *) buf;
	len >>= 1;

	for (i = 0; i < len; i++)
		p[i] = readw(nand->IO_ADDR_R);
}