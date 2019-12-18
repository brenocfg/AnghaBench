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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int board_ext_data_addr; int reserved_ram_size; int uarttx_pin; int uarttx_rate; int refclk_hz; } ;
struct TYPE_3__ {scalar_t__ target_ver; } ;
struct ath6kl {int conf_flags; int vif_max; int max_norm_iface; scalar_t__ target_type; TYPE_2__ hw; TYPE_1__ version; scalar_t__ p2p; int /*<<< orphan*/  fw_capabilities; } ;

/* Variables and functions */
 scalar_t__ AR6004_HW_1_3_VERSION ; 
 scalar_t__ AR6004_HW_3_0_VERSION ; 
 int ATH6KL_CONF_UART_DEBUG ; 
 int /*<<< orphan*/  ATH6KL_DBG_TRC ; 
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_STA_P2PDEV_DUPLEX ; 
 int EIO ; 
 int HI_OPTION_FW_BRIDGE_SHIFT ; 
 int HI_OPTION_FW_MODE_BITS ; 
 int HI_OPTION_FW_MODE_BSS_STA ; 
 int HI_OPTION_FW_MODE_SHIFT ; 
 int HI_OPTION_FW_SUBMODE_BITS ; 
 int HI_OPTION_FW_SUBMODE_NONE ; 
 int HI_OPTION_FW_SUBMODE_P2PDEV ; 
 int HI_OPTION_FW_SUBMODE_SHIFT ; 
 int HI_OPTION_MAC_ADDR_METHOD_SHIFT ; 
 int HI_OPTION_NUM_DEV_SHIFT ; 
 int HTC_PROTOCOL_VERSION ; 
 int /*<<< orphan*/  MBOX_YIELD_LIMIT ; 
 scalar_t__ TARGET_TYPE_AR6003 ; 
 scalar_t__ ath6kl_bmi_read_hi32 (struct ath6kl*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ath6kl_bmi_write_hi32 (struct ath6kl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 scalar_t__ ath6kl_set_htc_params (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi_app_host_interest ; 
 int /*<<< orphan*/  hi_board_ext_data ; 
 int /*<<< orphan*/  hi_dbg_uart_txpin ; 
 int /*<<< orphan*/  hi_desired_baud_rate ; 
 int /*<<< orphan*/  hi_end_ram_reserve_sz ; 
 int /*<<< orphan*/  hi_option_flag ; 
 int /*<<< orphan*/  hi_refclk_hz ; 
 int /*<<< orphan*/  hi_serial_enable ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath6kl_configure_target(struct ath6kl *ar)
{
	u32 param, ram_reserved_size;
	u8 fw_iftype, fw_mode = 0, fw_submode = 0;
	int i, status;

	param = !!(ar->conf_flags & ATH6KL_CONF_UART_DEBUG);
	if (ath6kl_bmi_write_hi32(ar, hi_serial_enable, param)) {
		ath6kl_err("bmi_write_memory for uart debug failed\n");
		return -EIO;
	}

	/*
	 * Note: Even though the firmware interface type is
	 * chosen as BSS_STA for all three interfaces, can
	 * be configured to IBSS/AP as long as the fw submode
	 * remains normal mode (0 - AP, STA and IBSS). But
	 * due to an target assert in firmware only one interface is
	 * configured for now.
	 */
	fw_iftype = HI_OPTION_FW_MODE_BSS_STA;

	for (i = 0; i < ar->vif_max; i++)
		fw_mode |= fw_iftype << (i * HI_OPTION_FW_MODE_BITS);

	/*
	 * Submodes when fw does not support dynamic interface
	 * switching:
	 *		vif[0] - AP/STA/IBSS
	 *		vif[1] - "P2P dev"/"P2P GO"/"P2P Client"
	 *		vif[2] - "P2P dev"/"P2P GO"/"P2P Client"
	 * Otherwise, All the interface are initialized to p2p dev.
	 */

	if (test_bit(ATH6KL_FW_CAPABILITY_STA_P2PDEV_DUPLEX,
		     ar->fw_capabilities)) {
		for (i = 0; i < ar->vif_max; i++)
			fw_submode |= HI_OPTION_FW_SUBMODE_P2PDEV <<
				(i * HI_OPTION_FW_SUBMODE_BITS);
	} else {
		for (i = 0; i < ar->max_norm_iface; i++)
			fw_submode |= HI_OPTION_FW_SUBMODE_NONE <<
				(i * HI_OPTION_FW_SUBMODE_BITS);

		for (i = ar->max_norm_iface; i < ar->vif_max; i++)
			fw_submode |= HI_OPTION_FW_SUBMODE_P2PDEV <<
				(i * HI_OPTION_FW_SUBMODE_BITS);

		if (ar->p2p && ar->vif_max == 1)
			fw_submode = HI_OPTION_FW_SUBMODE_P2PDEV;
	}

	if (ath6kl_bmi_write_hi32(ar, hi_app_host_interest,
				  HTC_PROTOCOL_VERSION) != 0) {
		ath6kl_err("bmi_write_memory for htc version failed\n");
		return -EIO;
	}

	/* set the firmware mode to STA/IBSS/AP */
	param = 0;

	if (ath6kl_bmi_read_hi32(ar, hi_option_flag, &param) != 0) {
		ath6kl_err("bmi_read_memory for setting fwmode failed\n");
		return -EIO;
	}

	param |= (ar->vif_max << HI_OPTION_NUM_DEV_SHIFT);
	param |= fw_mode << HI_OPTION_FW_MODE_SHIFT;
	param |= fw_submode << HI_OPTION_FW_SUBMODE_SHIFT;

	param |= (0 << HI_OPTION_MAC_ADDR_METHOD_SHIFT);
	param |= (0 << HI_OPTION_FW_BRIDGE_SHIFT);

	if (ath6kl_bmi_write_hi32(ar, hi_option_flag, param) != 0) {
		ath6kl_err("bmi_write_memory for setting fwmode failed\n");
		return -EIO;
	}

	ath6kl_dbg(ATH6KL_DBG_TRC, "firmware mode set\n");

	/*
	 * Hardcode the address use for the extended board data
	 * Ideally this should be pre-allocate by the OS at boot time
	 * But since it is a new feature and board data is loaded
	 * at init time, we have to workaround this from host.
	 * It is difficult to patch the firmware boot code,
	 * but possible in theory.
	 */

	if ((ar->target_type == TARGET_TYPE_AR6003) ||
	    (ar->version.target_ver == AR6004_HW_1_3_VERSION) ||
	    (ar->version.target_ver == AR6004_HW_3_0_VERSION)) {
		param = ar->hw.board_ext_data_addr;
		ram_reserved_size = ar->hw.reserved_ram_size;

		if (ath6kl_bmi_write_hi32(ar, hi_board_ext_data, param) != 0) {
			ath6kl_err("bmi_write_memory for hi_board_ext_data failed\n");
			return -EIO;
		}

		if (ath6kl_bmi_write_hi32(ar, hi_end_ram_reserve_sz,
					  ram_reserved_size) != 0) {
			ath6kl_err("bmi_write_memory for hi_end_ram_reserve_sz failed\n");
			return -EIO;
		}
	}

	/* set the block size for the target */
	if (ath6kl_set_htc_params(ar, MBOX_YIELD_LIMIT, 0))
		/* use default number of control buffers */
		return -EIO;

	/* Configure GPIO AR600x UART */
	status = ath6kl_bmi_write_hi32(ar, hi_dbg_uart_txpin,
				       ar->hw.uarttx_pin);
	if (status)
		return status;

	/* Only set the baud rate if we're actually doing debug */
	if (ar->conf_flags & ATH6KL_CONF_UART_DEBUG) {
		status = ath6kl_bmi_write_hi32(ar, hi_desired_baud_rate,
					       ar->hw.uarttx_rate);
		if (status)
			return status;
	}

	/* Configure target refclk_hz */
	if (ar->hw.refclk_hz != 0) {
		status = ath6kl_bmi_write_hi32(ar, hi_refclk_hz,
					       ar->hw.refclk_hz);
		if (status)
			return status;
	}

	return 0;
}