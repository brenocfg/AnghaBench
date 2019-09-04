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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int read_page (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int docg4_read_page_raw(struct mtd_info *mtd, struct nand_chip *nand,
			       uint8_t *buf, int oob_required, int page)
{
	return read_page(mtd, nand, buf, page, false);
}