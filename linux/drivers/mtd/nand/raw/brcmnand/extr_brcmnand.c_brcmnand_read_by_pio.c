#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nand_chip {int dummy; } ;
struct mtd_info {unsigned int oobsize; } ;
struct TYPE_2__ {int /*<<< orphan*/  sector_size_1k; } ;
struct brcmnand_host {TYPE_1__ hwcfg; struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {int /*<<< orphan*/  soc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_PAGE_READ ; 
 int EBADMSG ; 
 int EUCLEAN ; 
 scalar_t__ FC_BYTES ; 
 int FC_WORDS ; 
 int /*<<< orphan*/  brcmnand_clear_ecc_addr (struct brcmnand_controller*) ; 
 int /*<<< orphan*/  brcmnand_get_correcc_addr (struct brcmnand_controller*) ; 
 int /*<<< orphan*/  brcmnand_get_uncorrecc_addr (struct brcmnand_controller*) ; 
 int /*<<< orphan*/  brcmnand_read_fc (struct brcmnand_controller*,int) ; 
 int /*<<< orphan*/  brcmnand_send_cmd (struct brcmnand_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmnand_set_cmd_addr (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmnand_soc_data_bus_prepare (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcmnand_soc_data_bus_unprepare (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcmnand_waitfunc (struct nand_chip*) ; 
 scalar_t__ likely (int /*<<< orphan*/ *) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  read_oob_from_regs (struct brcmnand_controller*,int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmnand_read_by_pio(struct mtd_info *mtd, struct nand_chip *chip,
				u64 addr, unsigned int trans, u32 *buf,
				u8 *oob, u64 *err_addr)
{
	struct brcmnand_host *host = nand_get_controller_data(chip);
	struct brcmnand_controller *ctrl = host->ctrl;
	int i, j, ret = 0;

	brcmnand_clear_ecc_addr(ctrl);

	for (i = 0; i < trans; i++, addr += FC_BYTES) {
		brcmnand_set_cmd_addr(mtd, addr);
		/* SPARE_AREA_READ does not use ECC, so just use PAGE_READ */
		brcmnand_send_cmd(host, CMD_PAGE_READ);
		brcmnand_waitfunc(chip);

		if (likely(buf)) {
			brcmnand_soc_data_bus_prepare(ctrl->soc, false);

			for (j = 0; j < FC_WORDS; j++, buf++)
				*buf = brcmnand_read_fc(ctrl, j);

			brcmnand_soc_data_bus_unprepare(ctrl->soc, false);
		}

		if (oob)
			oob += read_oob_from_regs(ctrl, i, oob,
					mtd->oobsize / trans,
					host->hwcfg.sector_size_1k);

		if (!ret) {
			*err_addr = brcmnand_get_uncorrecc_addr(ctrl);

			if (*err_addr)
				ret = -EBADMSG;
		}

		if (!ret) {
			*err_addr = brcmnand_get_correcc_addr(ctrl);

			if (*err_addr)
				ret = -EUCLEAN;
		}
	}

	return ret;
}