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
struct trf7970a {int modulator_sys_clk_ctrl; int technology; int iso_ctrl; int /*<<< orphan*/  dev; void* guard_time; int /*<<< orphan*/  iso_ctrl_tech; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NFC_DIGITAL_RF_TECH_106A 132 
#define  NFC_DIGITAL_RF_TECH_106B 131 
#define  NFC_DIGITAL_RF_TECH_212F 130 
#define  NFC_DIGITAL_RF_TECH_424F 129 
#define  NFC_DIGITAL_RF_TECH_ISO15693 128 
 void* TRF7970A_GUARD_TIME_15693 ; 
 void* TRF7970A_GUARD_TIME_NFCA ; 
 void* TRF7970A_GUARD_TIME_NFCB ; 
 void* TRF7970A_GUARD_TIME_NFCF ; 
 int /*<<< orphan*/  TRF7970A_ISO_CTRL_14443A_106 ; 
 int /*<<< orphan*/  TRF7970A_ISO_CTRL_14443B_106 ; 
 int /*<<< orphan*/  TRF7970A_ISO_CTRL_15693_SGL_1OF4_2648 ; 
 int /*<<< orphan*/  TRF7970A_ISO_CTRL_FELICA_212 ; 
 int /*<<< orphan*/  TRF7970A_ISO_CTRL_FELICA_424 ; 
 int TRF7970A_MODULATOR_DEPTH_ASK10 ; 
 int TRF7970A_MODULATOR_DEPTH_OOK ; 
 int /*<<< orphan*/  TRF7970A_NFC_TARGET_LEVEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int trf7970a_write (struct trf7970a*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trf7970a_in_config_rf_tech(struct trf7970a *trf, int tech)
{
	int ret = 0;

	dev_dbg(trf->dev, "rf technology: %d\n", tech);

	switch (tech) {
	case NFC_DIGITAL_RF_TECH_106A:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_14443A_106;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_OOK;
		trf->guard_time = TRF7970A_GUARD_TIME_NFCA;
		break;
	case NFC_DIGITAL_RF_TECH_106B:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_14443B_106;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_ASK10;
		trf->guard_time = TRF7970A_GUARD_TIME_NFCB;
		break;
	case NFC_DIGITAL_RF_TECH_212F:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_FELICA_212;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_ASK10;
		trf->guard_time = TRF7970A_GUARD_TIME_NFCF;
		break;
	case NFC_DIGITAL_RF_TECH_424F:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_FELICA_424;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_ASK10;
		trf->guard_time = TRF7970A_GUARD_TIME_NFCF;
		break;
	case NFC_DIGITAL_RF_TECH_ISO15693:
		trf->iso_ctrl_tech = TRF7970A_ISO_CTRL_15693_SGL_1OF4_2648;
		trf->modulator_sys_clk_ctrl =
		    (trf->modulator_sys_clk_ctrl & 0xf8) |
		    TRF7970A_MODULATOR_DEPTH_OOK;
		trf->guard_time = TRF7970A_GUARD_TIME_15693;
		break;
	default:
		dev_dbg(trf->dev, "Unsupported rf technology: %d\n", tech);
		return -EINVAL;
	}

	trf->technology = tech;

	/* If in initiator mode and not changing the RF tech due to a
	 * PSL sequence (indicated by 'trf->iso_ctrl == 0xff' from
	 * trf7970a_init()), clear the NFC Target Detection Level register
	 * due to erratum.
	 */
	if (trf->iso_ctrl == 0xff)
		ret = trf7970a_write(trf, TRF7970A_NFC_TARGET_LEVEL, 0);

	return ret;
}