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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_2__ {int* cache; int limiting_active; int reset_needed; } ;
struct hfi1_pportdata {int link_speed_supported; int link_speed_enabled; int /*<<< orphan*/  dd; TYPE_1__ qsfp_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPA_INVALID_INDEX ; 
 int OPA_LINK_SPEED_12_5G ; 
 int OPA_LINK_SPEED_25G ; 
 int /*<<< orphan*/  PLATFORM_CONFIG_PORT_TABLE ; 
 int /*<<< orphan*/  PORT_TABLE_LOCAL_ATTEN_12G ; 
 int /*<<< orphan*/  PORT_TABLE_LOCAL_ATTEN_25G ; 
 int /*<<< orphan*/  PORT_TABLE_RX_PRESET_IDX ; 
 int /*<<< orphan*/  PORT_TABLE_TX_PRESET_IDX_ACTIVE_EQ ; 
 int /*<<< orphan*/  PORT_TABLE_TX_PRESET_IDX_ACTIVE_NO_EQ ; 
 size_t QSFP_EQ_INFO_OFFS ; 
 int /*<<< orphan*/  apply_cdr_settings (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_eq_settings (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_rx_amplitude_settings (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_platform_config_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int qual_bitrate (struct hfi1_pportdata*) ; 
 int qual_power (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  refresh_qsfp_cache (struct hfi1_pportdata*,TYPE_1__*) ; 
 int reset_qsfp (struct hfi1_pportdata*) ; 
 int set_qsfp_high_power (struct hfi1_pportdata*) ; 
 int set_qsfp_tx (struct hfi1_pportdata*,int) ; 

__attribute__((used)) static int tune_active_qsfp(struct hfi1_pportdata *ppd, u32 *ptr_tx_preset,
			    u32 *ptr_rx_preset, u32 *ptr_total_atten)
{
	int ret;
	u16 lss = ppd->link_speed_supported, lse = ppd->link_speed_enabled;
	u8 *cache = ppd->qsfp_info.cache;

	ppd->qsfp_info.limiting_active = 1;

	ret = set_qsfp_tx(ppd, 0);
	if (ret)
		return ret;

	ret = qual_power(ppd);
	if (ret)
		return ret;

	ret = qual_bitrate(ppd);
	if (ret)
		return ret;

	/*
	 * We'll change the QSFP memory contents from here on out, thus we set a
	 * flag here to remind ourselves to reset the QSFP module. This prevents
	 * reuse of stale settings established in our previous pass through.
	 */
	if (ppd->qsfp_info.reset_needed) {
		ret = reset_qsfp(ppd);
		if (ret)
			return ret;
		refresh_qsfp_cache(ppd, &ppd->qsfp_info);
	} else {
		ppd->qsfp_info.reset_needed = 1;
	}

	ret = set_qsfp_high_power(ppd);
	if (ret)
		return ret;

	if (cache[QSFP_EQ_INFO_OFFS] & 0x4) {
		ret = get_platform_config_field(
			ppd->dd,
			PLATFORM_CONFIG_PORT_TABLE, 0,
			PORT_TABLE_TX_PRESET_IDX_ACTIVE_EQ,
			ptr_tx_preset, 4);
		if (ret) {
			*ptr_tx_preset = OPA_INVALID_INDEX;
			return ret;
		}
	} else {
		ret = get_platform_config_field(
			ppd->dd,
			PLATFORM_CONFIG_PORT_TABLE, 0,
			PORT_TABLE_TX_PRESET_IDX_ACTIVE_NO_EQ,
			ptr_tx_preset, 4);
		if (ret) {
			*ptr_tx_preset = OPA_INVALID_INDEX;
			return ret;
		}
	}

	ret = get_platform_config_field(
		ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
		PORT_TABLE_RX_PRESET_IDX, ptr_rx_preset, 4);
	if (ret) {
		*ptr_rx_preset = OPA_INVALID_INDEX;
		return ret;
	}

	if ((lss & OPA_LINK_SPEED_25G) && (lse & OPA_LINK_SPEED_25G))
		get_platform_config_field(
			ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
			PORT_TABLE_LOCAL_ATTEN_25G, ptr_total_atten, 4);
	else if ((lss & OPA_LINK_SPEED_12_5G) && (lse & OPA_LINK_SPEED_12_5G))
		get_platform_config_field(
			ppd->dd, PLATFORM_CONFIG_PORT_TABLE, 0,
			PORT_TABLE_LOCAL_ATTEN_12G, ptr_total_atten, 4);

	apply_cdr_settings(ppd, *ptr_rx_preset, *ptr_tx_preset);

	apply_eq_settings(ppd, *ptr_rx_preset, *ptr_tx_preset);

	apply_rx_amplitude_settings(ppd, *ptr_rx_preset, *ptr_tx_preset);

	ret = set_qsfp_tx(ppd, 1);

	return ret;
}