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

/* Variables and functions */
 int /*<<< orphan*/  nand_change_write_column_op (struct nand_chip*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tango_write_buf (struct nand_chip*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void aux_write(struct nand_chip *chip, const u8 **buf, int len, int *pos)
{
	*pos += len;

	if (!*buf) {
		/* skip over "len" bytes */
		nand_change_write_column_op(chip, *pos, NULL, 0, false);
	} else {
		tango_write_buf(chip, *buf, len);
		*buf += len;
	}
}