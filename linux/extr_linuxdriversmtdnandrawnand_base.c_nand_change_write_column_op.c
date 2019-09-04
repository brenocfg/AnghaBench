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
struct nand_sdr_timings {int /*<<< orphan*/  tCCS_min; } ;
struct nand_operation {int /*<<< orphan*/  ninstrs; } ;
struct TYPE_3__ {int force_8bit; } ;
struct TYPE_4__ {TYPE_1__ data; } ;
struct nand_op_instr {TYPE_2__ ctx; } ;
struct nand_chip {int /*<<< orphan*/  (* write_buf ) (struct mtd_info*,void const*,unsigned int) ;int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,unsigned int,int) ;int /*<<< orphan*/  data_interface; scalar_t__ exec_op; } ;
struct mtd_info {unsigned int writesize; unsigned int oobsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  NAND_CMD_RNDIN ; 
 struct nand_operation NAND_OPERATION (struct nand_op_instr*) ; 
 struct nand_op_instr NAND_OP_ADDR (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_DATA_OUT (unsigned int,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSEC_TO_NSEC (int /*<<< orphan*/ ) ; 
 int nand_exec_op (struct nand_chip*,struct nand_operation*) ; 
 int nand_fill_column_cycles (struct nand_chip*,int /*<<< orphan*/ *,unsigned int) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (int /*<<< orphan*/ *) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,void const*,unsigned int) ; 

int nand_change_write_column_op(struct nand_chip *chip,
				unsigned int offset_in_page,
				const void *buf, unsigned int len,
				bool force_8bit)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (len && !buf)
		return -EINVAL;

	if (offset_in_page + len > mtd->writesize + mtd->oobsize)
		return -EINVAL;

	/* Small page NANDs do not support column change. */
	if (mtd->writesize <= 512)
		return -ENOTSUPP;

	if (chip->exec_op) {
		const struct nand_sdr_timings *sdr =
			nand_get_sdr_timings(&chip->data_interface);
		u8 addrs[2];
		struct nand_op_instr instrs[] = {
			NAND_OP_CMD(NAND_CMD_RNDIN, 0),
			NAND_OP_ADDR(2, addrs, PSEC_TO_NSEC(sdr->tCCS_min)),
			NAND_OP_DATA_OUT(len, buf, 0),
		};
		struct nand_operation op = NAND_OPERATION(instrs);
		int ret;

		ret = nand_fill_column_cycles(chip, addrs, offset_in_page);
		if (ret < 0)
			return ret;

		instrs[2].ctx.data.force_8bit = force_8bit;

		/* Drop the DATA_OUT instruction if len is set to 0. */
		if (!len)
			op.ninstrs--;

		return nand_exec_op(chip, &op);
	}

	chip->cmdfunc(mtd, NAND_CMD_RNDIN, offset_in_page, -1);
	if (len)
		chip->write_buf(mtd, buf, len);

	return 0;
}