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
struct nand_sdr_timings {int tRC_min; } ;
struct nand_data_interface {int dummy; } ;
struct nand_chip {int dummy; } ;
struct mxic_nand_ctlr {scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DATA_STROB ; 
 int /*<<< orphan*/  DATA_STROB_EDO_EN ; 
 scalar_t__ IS_ERR (struct nand_sdr_timings const*) ; 
 int NAND_DATA_IFACE_CHECK_ONLY ; 
 int NSEC_PER_SEC ; 
 int PTR_ERR (struct nand_sdr_timings const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int mxic_nfc_set_freq (struct mxic_nand_ctlr*,unsigned long) ; 
 struct mxic_nand_ctlr* nand_get_controller_data (struct nand_chip*) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (struct nand_data_interface const*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mxic_nfc_setup_data_interface(struct nand_chip *chip, int chipnr,
					 const struct nand_data_interface *conf)
{
	struct mxic_nand_ctlr *nfc = nand_get_controller_data(chip);
	const struct nand_sdr_timings *sdr;
	unsigned long freq;
	int ret;

	sdr = nand_get_sdr_timings(conf);
	if (IS_ERR(sdr))
		return PTR_ERR(sdr);

	if (chipnr == NAND_DATA_IFACE_CHECK_ONLY)
		return 0;

	freq = NSEC_PER_SEC / (sdr->tRC_min / 1000);

	ret =  mxic_nfc_set_freq(nfc, freq);
	if (ret)
		dev_err(nfc->dev, "set freq:%ld failed\n", freq);

	if (sdr->tRC_min < 30000)
		writel(DATA_STROB_EDO_EN, nfc->regs + DATA_STROB);

	return 0;
}