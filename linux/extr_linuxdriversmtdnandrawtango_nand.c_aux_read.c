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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_change_read_column_op (struct nand_chip*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  tango_read_buf (struct mtd_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void aux_read(struct nand_chip *chip, u8 **buf, int len, int *pos)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	*pos += len;

	if (!*buf) {
		/* skip over "len" bytes */
		nand_change_read_column_op(chip, *pos, NULL, 0, false);
	} else {
		tango_read_buf(mtd, *buf, len);
		*buf += len;
	}
}