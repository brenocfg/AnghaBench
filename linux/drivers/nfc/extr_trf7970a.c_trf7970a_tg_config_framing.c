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
typedef  scalar_t__ u8 ;
struct trf7970a {scalar_t__ iso_ctrl_tech; scalar_t__ iso_ctrl; int framing; scalar_t__ modulator_sys_clk_ctrl; scalar_t__ chip_status_ctrl; int /*<<< orphan*/  dev; void* tx_cmd; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NFC_DIGITAL_FRAMING_NFCA_ANTICOL_COMPLETE 133 
#define  NFC_DIGITAL_FRAMING_NFCA_NFC_DEP 132 
#define  NFC_DIGITAL_FRAMING_NFCA_STANDARD 131 
#define  NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A 130 
#define  NFC_DIGITAL_FRAMING_NFCF_NFC_DEP 129 
#define  NFC_DIGITAL_FRAMING_NFC_DEP_ACTIVATED 128 
 int /*<<< orphan*/  TRF7970A_CHIP_STATUS_CTRL ; 
 scalar_t__ TRF7970A_CHIP_STATUS_RF_ON ; 
 void* TRF7970A_CMD_TRANSMIT ; 
 void* TRF7970A_CMD_TRANSMIT_NO_CRC ; 
 int /*<<< orphan*/  TRF7970A_ISO_CTRL ; 
 scalar_t__ TRF7970A_ISO_CTRL_RX_CRC_N ; 
 int /*<<< orphan*/  TRF7970A_MODULATOR_SYS_CLK_CTRL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int trf7970a_write (struct trf7970a*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int trf7970a_tg_config_framing(struct trf7970a *trf, int framing)
{
	u8 iso_ctrl = trf->iso_ctrl_tech;
	int ret;

	dev_dbg(trf->dev, "framing: %d\n", framing);

	switch (framing) {
	case NFC_DIGITAL_FRAMING_NFCA_NFC_DEP:
		trf->tx_cmd = TRF7970A_CMD_TRANSMIT_NO_CRC;
		iso_ctrl |= TRF7970A_ISO_CTRL_RX_CRC_N;
		break;
	case NFC_DIGITAL_FRAMING_NFCA_STANDARD:
	case NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A:
	case NFC_DIGITAL_FRAMING_NFCA_ANTICOL_COMPLETE:
		/* These ones are applied in the interrupt handler */
		iso_ctrl = trf->iso_ctrl; /* Don't write to ISO_CTRL yet */
		break;
	case NFC_DIGITAL_FRAMING_NFCF_NFC_DEP:
		trf->tx_cmd = TRF7970A_CMD_TRANSMIT;
		iso_ctrl &= ~TRF7970A_ISO_CTRL_RX_CRC_N;
		break;
	case NFC_DIGITAL_FRAMING_NFC_DEP_ACTIVATED:
		trf->tx_cmd = TRF7970A_CMD_TRANSMIT;
		iso_ctrl &= ~TRF7970A_ISO_CTRL_RX_CRC_N;
		break;
	default:
		dev_dbg(trf->dev, "Unsupported Framing: %d\n", framing);
		return -EINVAL;
	}

	trf->framing = framing;

	if (iso_ctrl != trf->iso_ctrl) {
		ret = trf7970a_write(trf, TRF7970A_ISO_CTRL, iso_ctrl);
		if (ret)
			return ret;

		trf->iso_ctrl = iso_ctrl;

		ret = trf7970a_write(trf, TRF7970A_MODULATOR_SYS_CLK_CTRL,
				     trf->modulator_sys_clk_ctrl);
		if (ret)
			return ret;
	}

	if (!(trf->chip_status_ctrl & TRF7970A_CHIP_STATUS_RF_ON)) {
		ret = trf7970a_write(trf, TRF7970A_CHIP_STATUS_CTRL,
				     trf->chip_status_ctrl |
				     TRF7970A_CHIP_STATUS_RF_ON);
		if (ret)
			return ret;

		trf->chip_status_ctrl |= TRF7970A_CHIP_STATUS_RF_ON;
	}

	return 0;
}