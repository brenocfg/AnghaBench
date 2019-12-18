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
typedef  int u8 ;
struct vnt_rsp_card_init {int /*<<< orphan*/  net_addr; int /*<<< orphan*/  rf_type; } ;
struct vnt_cmd_card_init {int /*<<< orphan*/  long_retry_limit; int /*<<< orphan*/  short_retry_limit; int /*<<< orphan*/ * sw_net_addr; int /*<<< orphan*/  exist_sw_net_addr; int /*<<< orphan*/  init_class; } ;
struct vnt_private {int local_id; int power; scalar_t__ cck_pwr; scalar_t__* eeprom; scalar_t__ ofdm_pwr_g; scalar_t__* cck_pwr_tbl; scalar_t__* ofdm_pwr_tbl; int ofdm_pwr_a; scalar_t__* ofdm_a_pwr_tbl; int tx_rx_ant_inv; int rx_antenna_sel; scalar_t__ bb_type; int short_slot_time; int radio_ctl; TYPE_1__* usb; int /*<<< orphan*/ * current_net_addr; int /*<<< orphan*/  permanent_net_addr; int /*<<< orphan*/  rf_type; int /*<<< orphan*/  auto_fb_ctrl; void* rx_antenna_mode; void* tx_antenna_mode; int /*<<< orphan*/  top_cck_basic_rate; int /*<<< orphan*/  top_ofdm_basic_rate; int /*<<< orphan*/  long_retry_limit; int /*<<< orphan*/  short_retry_limit; int /*<<< orphan*/  exist_sw_net_addr; int /*<<< orphan*/  packet_type; struct vnt_rsp_card_init init_response; struct vnt_cmd_card_init init_command; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* ANT_A ; 
 void* ANT_B ; 
 int /*<<< orphan*/  AUTO_FB_0 ; 
 scalar_t__ BB_TYPE_11A ; 
 scalar_t__ BB_TYPE_11G ; 
 int CB_MAX_CHANNEL_5G ; 
 int /*<<< orphan*/  DEVICE_INIT_COLD ; 
 int EEP_ANTENNA_AUX ; 
 int EEP_ANTENNA_MAIN ; 
 int EEP_ANTINV ; 
 size_t EEP_OFS_ANTENNA ; 
 size_t EEP_OFS_CALIB_RX_IQ ; 
 size_t EEP_OFS_CALIB_TX_DC ; 
 size_t EEP_OFS_CALIB_TX_IQ ; 
 int EEP_OFS_CCK_PWR_TBL ; 
 size_t EEP_OFS_MAJOR_VER ; 
 size_t EEP_OFS_MINOR_VER ; 
 int EEP_OFS_OFDMA_PWR_TBL ; 
 int EEP_OFS_OFDM_PWR_TBL ; 
 size_t EEP_OFS_PWR_CCK ; 
 size_t EEP_OFS_PWR_OFDMG ; 
 size_t EEP_OFS_RADIOCTL ; 
 int EEP_RADIOCTL_ENABLE ; 
 int GPIO3_DATA ; 
 int GPIO3_INTMD ; 
 int LEDSTS_SLOW ; 
 int /*<<< orphan*/  LEDSTS_STS ; 
 int /*<<< orphan*/  LEDSTS_TMLEN ; 
 int /*<<< orphan*/  MAC_REG_GPIOCTL0 ; 
 int /*<<< orphan*/  MAC_REG_GPIOCTL1 ; 
 int /*<<< orphan*/  MAC_REG_LOCALID ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_BBREG ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_MACREG ; 
 int /*<<< orphan*/  MESSAGE_TYPE_CARDINIT ; 
 int /*<<< orphan*/  MESSAGE_TYPE_INIT_RSP ; 
 int /*<<< orphan*/  MESSAGE_TYPE_READ ; 
 int /*<<< orphan*/  RATE_1M ; 
 int /*<<< orphan*/  RATE_24M ; 
 int /*<<< orphan*/  RF_VT3226D0 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vnt_check_firmware_version (struct vnt_private*) ; 
 int vnt_control_in (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int vnt_control_out_u8 (struct vnt_private*,int /*<<< orphan*/ ,int,int) ; 
 int vnt_download_firmware (struct vnt_private*) ; 
 int vnt_firmware_branch_to_sram (struct vnt_private*) ; 
 int vnt_mac_reg_bits_off (struct vnt_private*,int /*<<< orphan*/ ,int) ; 
 int vnt_mac_reg_bits_on (struct vnt_private*,int /*<<< orphan*/ ,int) ; 
 int vnt_mac_set_led (struct vnt_private*,int /*<<< orphan*/ ,int) ; 
 int vnt_radio_power_on (struct vnt_private*) ; 
 int vnt_set_antenna_mode (struct vnt_private*,void*) ; 
 int vnt_set_short_slot_time (struct vnt_private*) ; 
 int vnt_vt3184_init (struct vnt_private*) ; 

__attribute__((used)) static int vnt_init_registers(struct vnt_private *priv)
{
	int ret = 0;
	struct vnt_cmd_card_init *init_cmd = &priv->init_command;
	struct vnt_rsp_card_init *init_rsp = &priv->init_response;
	u8 antenna;
	int ii;
	u8 tmp;
	u8 calib_tx_iq = 0, calib_tx_dc = 0, calib_rx_iq = 0;

	dev_dbg(&priv->usb->dev, "---->INIbInitAdapter. [%d][%d]\n",
		DEVICE_INIT_COLD, priv->packet_type);

	ret = vnt_check_firmware_version(priv);
	if (ret) {
		ret = vnt_download_firmware(priv);
		if (ret) {
			dev_dbg(&priv->usb->dev,
				"Could not download firmware: %d.\n", ret);
			goto end;
		}

		ret = vnt_firmware_branch_to_sram(priv);
		if (ret) {
			dev_dbg(&priv->usb->dev,
				"Could not branch to SRAM: %d.\n", ret);
			goto end;
		}
	}

	ret = vnt_vt3184_init(priv);
	if (ret) {
		dev_dbg(&priv->usb->dev, "vnt_vt3184_init fail\n");
		goto end;
	}

	init_cmd->init_class = DEVICE_INIT_COLD;
	init_cmd->exist_sw_net_addr = priv->exist_sw_net_addr;
	for (ii = 0; ii < 6; ii++)
		init_cmd->sw_net_addr[ii] = priv->current_net_addr[ii];
	init_cmd->short_retry_limit = priv->short_retry_limit;
	init_cmd->long_retry_limit = priv->long_retry_limit;

	/* issue card_init command to device */
	ret = vnt_control_out(priv, MESSAGE_TYPE_CARDINIT, 0, 0,
			      sizeof(struct vnt_cmd_card_init),
			      (u8 *)init_cmd);
	if (ret) {
		dev_dbg(&priv->usb->dev, "Issue Card init fail\n");
		goto end;
	}

	ret = vnt_control_in(priv, MESSAGE_TYPE_INIT_RSP, 0, 0,
			     sizeof(struct vnt_rsp_card_init),
			     (u8 *)init_rsp);
	if (ret) {
		dev_dbg(&priv->usb->dev, "Cardinit request in status fail!\n");
		goto end;
	}

	/* local ID for AES functions */
	ret = vnt_control_in(priv, MESSAGE_TYPE_READ, MAC_REG_LOCALID,
			     MESSAGE_REQUEST_MACREG, 1, &priv->local_id);
	if (ret)
		goto end;

	/* do MACbSoftwareReset in MACvInitialize */

	priv->top_ofdm_basic_rate = RATE_24M;
	priv->top_cck_basic_rate = RATE_1M;

	/* target to IF pin while programming to RF chip */
	priv->power = 0xFF;

	priv->cck_pwr = priv->eeprom[EEP_OFS_PWR_CCK];
	priv->ofdm_pwr_g = priv->eeprom[EEP_OFS_PWR_OFDMG];
	/* load power table */
	for (ii = 0; ii < 14; ii++) {
		priv->cck_pwr_tbl[ii] =
			priv->eeprom[ii + EEP_OFS_CCK_PWR_TBL];
		if (priv->cck_pwr_tbl[ii] == 0)
			priv->cck_pwr_tbl[ii] = priv->cck_pwr;

		priv->ofdm_pwr_tbl[ii] =
				priv->eeprom[ii + EEP_OFS_OFDM_PWR_TBL];
		if (priv->ofdm_pwr_tbl[ii] == 0)
			priv->ofdm_pwr_tbl[ii] = priv->ofdm_pwr_g;
	}

	/*
	 * original zonetype is USA, but custom zonetype is Europe,
	 * then need to recover 12, 13, 14 channels with 11 channel
	 */
	for (ii = 11; ii < 14; ii++) {
		priv->cck_pwr_tbl[ii] = priv->cck_pwr_tbl[10];
		priv->ofdm_pwr_tbl[ii] = priv->ofdm_pwr_tbl[10];
	}

	priv->ofdm_pwr_a = 0x34; /* same as RFbMA2829SelectChannel */

	/* load OFDM A power table */
	for (ii = 0; ii < CB_MAX_CHANNEL_5G; ii++) {
		priv->ofdm_a_pwr_tbl[ii] =
			priv->eeprom[ii + EEP_OFS_OFDMA_PWR_TBL];

		if (priv->ofdm_a_pwr_tbl[ii] == 0)
			priv->ofdm_a_pwr_tbl[ii] = priv->ofdm_pwr_a;
	}

	antenna = priv->eeprom[EEP_OFS_ANTENNA];

	if (antenna & EEP_ANTINV)
		priv->tx_rx_ant_inv = true;
	else
		priv->tx_rx_ant_inv = false;

	antenna &= (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN);

	if (antenna == 0) /* if not set default is both */
		antenna = (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN);

	if (antenna == (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN)) {
		priv->tx_antenna_mode = ANT_B;
		priv->rx_antenna_sel = 1;

		if (priv->tx_rx_ant_inv)
			priv->rx_antenna_mode = ANT_A;
		else
			priv->rx_antenna_mode = ANT_B;
	} else  {
		priv->rx_antenna_sel = 0;

		if (antenna & EEP_ANTENNA_AUX) {
			priv->tx_antenna_mode = ANT_A;

			if (priv->tx_rx_ant_inv)
				priv->rx_antenna_mode = ANT_B;
			else
				priv->rx_antenna_mode = ANT_A;
		} else {
			priv->tx_antenna_mode = ANT_B;

		if (priv->tx_rx_ant_inv)
			priv->rx_antenna_mode = ANT_A;
		else
			priv->rx_antenna_mode = ANT_B;
		}
	}

	/* Set initial antenna mode */
	ret = vnt_set_antenna_mode(priv, priv->rx_antenna_mode);
	if (ret)
		goto end;

	/* get Auto Fall Back type */
	priv->auto_fb_ctrl = AUTO_FB_0;

	/* default Auto Mode */
	priv->bb_type = BB_TYPE_11G;

	/* get RFType */
	priv->rf_type = init_rsp->rf_type;

	/* load vt3266 calibration parameters in EEPROM */
	if (priv->rf_type == RF_VT3226D0) {
		if ((priv->eeprom[EEP_OFS_MAJOR_VER] == 0x1) &&
		    (priv->eeprom[EEP_OFS_MINOR_VER] >= 0x4)) {
			calib_tx_iq = priv->eeprom[EEP_OFS_CALIB_TX_IQ];
			calib_tx_dc = priv->eeprom[EEP_OFS_CALIB_TX_DC];
			calib_rx_iq = priv->eeprom[EEP_OFS_CALIB_RX_IQ];
			if (calib_tx_iq || calib_tx_dc || calib_rx_iq) {
				/* CR255, enable TX/RX IQ and
				 * DC compensation mode
				 */
				ret = vnt_control_out_u8(priv,
							 MESSAGE_REQUEST_BBREG,
							 0xff, 0x03);
				if (ret)
					goto end;

				/* CR251, TX I/Q Imbalance Calibration */
				ret = vnt_control_out_u8(priv,
							 MESSAGE_REQUEST_BBREG,
							 0xfb, calib_tx_iq);
				if (ret)
					goto end;

				/* CR252, TX DC-Offset Calibration */
				ret = vnt_control_out_u8(priv,
							 MESSAGE_REQUEST_BBREG,
							 0xfC, calib_tx_dc);
				if (ret)
					goto end;

				/* CR253, RX I/Q Imbalance Calibration */
				ret = vnt_control_out_u8(priv,
							 MESSAGE_REQUEST_BBREG,
							 0xfd, calib_rx_iq);
				if (ret)
					goto end;
			} else {
				/* CR255, turn off
				 * BB Calibration compensation
				 */
				ret = vnt_control_out_u8(priv,
							 MESSAGE_REQUEST_BBREG,
							 0xff, 0x0);
				if (ret)
					goto end;
			}
		}
	}

	/* get permanent network address */
	memcpy(priv->permanent_net_addr, init_rsp->net_addr, 6);
	ether_addr_copy(priv->current_net_addr, priv->permanent_net_addr);

	/* if exist SW network address, use it */
	dev_dbg(&priv->usb->dev, "Network address = %pM\n",
		priv->current_net_addr);

	/*
	 * set BB and packet type at the same time
	 * set Short Slot Time, xIFS, and RSPINF
	 */
	if (priv->bb_type == BB_TYPE_11A)
		priv->short_slot_time = true;
	else
		priv->short_slot_time = false;

	ret = vnt_set_short_slot_time(priv);
	if (ret)
		goto end;

	priv->radio_ctl = priv->eeprom[EEP_OFS_RADIOCTL];

	if ((priv->radio_ctl & EEP_RADIOCTL_ENABLE) != 0) {
		ret = vnt_control_in(priv, MESSAGE_TYPE_READ,
				     MAC_REG_GPIOCTL1, MESSAGE_REQUEST_MACREG,
				     1, &tmp);
		if (ret)
			goto end;

		if ((tmp & GPIO3_DATA) == 0) {
			ret = vnt_mac_reg_bits_on(priv, MAC_REG_GPIOCTL1,
						  GPIO3_INTMD);
		} else {
			ret = vnt_mac_reg_bits_off(priv, MAC_REG_GPIOCTL1,
						   GPIO3_INTMD);
		}

		if (ret)
			goto end;
	}


	ret = vnt_mac_set_led(priv, LEDSTS_TMLEN, 0x38);
	if (ret)
		goto end;

	ret = vnt_mac_set_led(priv, LEDSTS_STS, LEDSTS_SLOW);
	if (ret)
		goto end;

	ret = vnt_mac_reg_bits_on(priv, MAC_REG_GPIOCTL0, 0x01);
	if (ret)
		goto end;

	ret = vnt_radio_power_on(priv);
	if (ret)
		goto end;

	dev_dbg(&priv->usb->dev, "<----INIbInitAdapter Exit\n");

end:
	return ret;
}