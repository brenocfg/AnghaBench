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
struct nand_sdr_timings {int /*<<< orphan*/  tADL_min; } ;
struct nand_operation {int /*<<< orphan*/  ninstrs; } ;
struct nand_op_instr {int dummy; } ;
struct nand_chip {int /*<<< orphan*/  (* read_byte ) (struct mtd_info*) ;int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  data_interface; scalar_t__ exec_op; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NAND_CMD_READID ; 
 struct nand_operation NAND_OPERATION (struct nand_op_instr*) ; 
 struct nand_op_instr NAND_OP_8BIT_DATA_IN (unsigned int,void*,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_ADDR (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSEC_TO_NSEC (int /*<<< orphan*/ ) ; 
 int nand_exec_op (struct nand_chip*,struct nand_operation*) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (int /*<<< orphan*/ *) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*) ; 

int nand_readid_op(struct nand_chip *chip, u8 addr, void *buf,
		   unsigned int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int i;
	u8 *id = buf;

	if (len && !buf)
		return -EINVAL;

	if (chip->exec_op) {
		const struct nand_sdr_timings *sdr =
			nand_get_sdr_timings(&chip->data_interface);
		struct nand_op_instr instrs[] = {
			NAND_OP_CMD(NAND_CMD_READID, 0),
			NAND_OP_ADDR(1, &addr, PSEC_TO_NSEC(sdr->tADL_min)),
			NAND_OP_8BIT_DATA_IN(len, buf, 0),
		};
		struct nand_operation op = NAND_OPERATION(instrs);

		/* Drop the DATA_IN instruction if len is set to 0. */
		if (!len)
			op.ninstrs--;

		return nand_exec_op(chip, &op);
	}

	chip->cmdfunc(mtd, NAND_CMD_READID, addr, -1);

	for (i = 0; i < len; i++)
		id[i] = chip->read_byte(mtd);

	return 0;
}