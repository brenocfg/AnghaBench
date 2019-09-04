#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct nand_operation {int dummy; } ;
struct TYPE_3__ {int force_8bit; } ;
struct TYPE_4__ {TYPE_1__ data; } ;
struct nand_op_instr {TYPE_2__ ctx; } ;
struct nand_chip {int /*<<< orphan*/  (* write_buf ) (struct mtd_info*,void const*,unsigned int) ;int /*<<< orphan*/  (* write_byte ) (struct mtd_info*,int /*<<< orphan*/  const) ;scalar_t__ exec_op; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nand_operation NAND_OPERATION (struct nand_op_instr*) ; 
 struct nand_op_instr NAND_OP_DATA_OUT (unsigned int,void const*,int /*<<< orphan*/ ) ; 
 int nand_exec_op (struct nand_chip*,struct nand_operation*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,void const*,unsigned int) ; 

int nand_write_data_op(struct nand_chip *chip, const void *buf,
		       unsigned int len, bool force_8bit)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (!len || !buf)
		return -EINVAL;

	if (chip->exec_op) {
		struct nand_op_instr instrs[] = {
			NAND_OP_DATA_OUT(len, buf, 0),
		};
		struct nand_operation op = NAND_OPERATION(instrs);

		instrs[0].ctx.data.force_8bit = force_8bit;

		return nand_exec_op(chip, &op);
	}

	if (force_8bit) {
		const u8 *p = buf;
		unsigned int i;

		for (i = 0; i < len; i++)
			chip->write_byte(mtd, p[i]);
	} else {
		chip->write_buf(mtd, buf, len);
	}

	return 0;
}