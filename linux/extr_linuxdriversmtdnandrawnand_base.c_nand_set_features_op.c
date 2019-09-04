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
struct nand_sdr_timings {int /*<<< orphan*/  tFEAT_max; int /*<<< orphan*/  tWB_max; int /*<<< orphan*/  tADL_min; } ;
struct nand_operation {int dummy; } ;
struct nand_op_instr {int dummy; } ;
struct nand_chip {int (* waitfunc ) (struct mtd_info*,struct nand_chip*) ;int /*<<< orphan*/  (* write_byte ) (struct mtd_info*,int /*<<< orphan*/  const) ;int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  data_interface; scalar_t__ exec_op; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NAND_CMD_SET_FEATURES ; 
 struct nand_operation NAND_OPERATION (struct nand_op_instr*) ; 
 struct nand_op_instr NAND_OP_8BIT_DATA_OUT (int,void const*,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_ADDR (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nand_op_instr NAND_OP_WAIT_RDY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NAND_STATUS_FAIL ; 
 int ONFI_SUBFEATURE_PARAM_LEN ; 
 int /*<<< orphan*/  PSEC_TO_MSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSEC_TO_NSEC (int /*<<< orphan*/ ) ; 
 int nand_exec_op (struct nand_chip*,struct nand_operation*) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (int /*<<< orphan*/ *) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/  const) ; 
 int stub3 (struct mtd_info*,struct nand_chip*) ; 

__attribute__((used)) static int nand_set_features_op(struct nand_chip *chip, u8 feature,
				const void *data)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	const u8 *params = data;
	int i, ret;

	if (chip->exec_op) {
		const struct nand_sdr_timings *sdr =
			nand_get_sdr_timings(&chip->data_interface);
		struct nand_op_instr instrs[] = {
			NAND_OP_CMD(NAND_CMD_SET_FEATURES, 0),
			NAND_OP_ADDR(1, &feature, PSEC_TO_NSEC(sdr->tADL_min)),
			NAND_OP_8BIT_DATA_OUT(ONFI_SUBFEATURE_PARAM_LEN, data,
					      PSEC_TO_NSEC(sdr->tWB_max)),
			NAND_OP_WAIT_RDY(PSEC_TO_MSEC(sdr->tFEAT_max), 0),
		};
		struct nand_operation op = NAND_OPERATION(instrs);

		return nand_exec_op(chip, &op);
	}

	chip->cmdfunc(mtd, NAND_CMD_SET_FEATURES, feature, -1);
	for (i = 0; i < ONFI_SUBFEATURE_PARAM_LEN; ++i)
		chip->write_byte(mtd, params[i]);

	ret = chip->waitfunc(mtd, chip);
	if (ret < 0)
		return ret;

	if (ret & NAND_STATUS_FAIL)
		return -EIO;

	return 0;
}