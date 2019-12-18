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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  SVCMAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_11AC ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_AP_DFS ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_AP_UAPSD ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_ATF ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_AUX_CHAN_LOAD_INTF ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_AUX_SPECTRAL_INTF ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_BB_TIMING_CONFIG_SUPPORT ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_BCN_FILTER ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_BCN_MISS_OFFLOAD ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_BEACON_OFFLOAD ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_BLOCKACK ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_BSS_CHANNEL_INFO_64 ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_BURST ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_COEX_GPIO ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_EXT_RES_CFG_SUPPORT ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_FORCE_FW_HANG ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_HTT_MGMT_TX_COMP_VALID_FLAGS ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_IRAM_TIDS ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_MESH ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_PEER_STATS ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_PER_PACKET_SW_ENCRYPT ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_PHYERR ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_RATECTRL ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_RATECTRL_CACHE ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_RESET_CHIP ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_ROAM_OFFLOAD ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_RTT ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_SCAN_OFFLOAD ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_SMART_ANTENNA_HW_SUPPORT ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_SMART_ANTENNA_SW_SUPPORT ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_STA_ADVANCED_PWRSAVE ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_STA_PWRSAVE ; 
 int /*<<< orphan*/  WMI_10X_SERVICE_WOW ; 
 int /*<<< orphan*/  WMI_SERVICE_11AC ; 
 int /*<<< orphan*/  WMI_SERVICE_AP_DFS ; 
 int /*<<< orphan*/  WMI_SERVICE_AP_UAPSD ; 
 int /*<<< orphan*/  WMI_SERVICE_ATF ; 
 int /*<<< orphan*/  WMI_SERVICE_AUX_CHAN_LOAD_INTF ; 
 int /*<<< orphan*/  WMI_SERVICE_AUX_SPECTRAL_INTF ; 
 int /*<<< orphan*/  WMI_SERVICE_BB_TIMING_CONFIG_SUPPORT ; 
 int /*<<< orphan*/  WMI_SERVICE_BCN_FILTER ; 
 int /*<<< orphan*/  WMI_SERVICE_BCN_MISS_OFFLOAD ; 
 int /*<<< orphan*/  WMI_SERVICE_BEACON_OFFLOAD ; 
 int /*<<< orphan*/  WMI_SERVICE_BLOCKACK ; 
 int /*<<< orphan*/  WMI_SERVICE_BSS_CHANNEL_INFO_64 ; 
 int /*<<< orphan*/  WMI_SERVICE_BURST ; 
 int /*<<< orphan*/  WMI_SERVICE_COEX_GPIO ; 
 int /*<<< orphan*/  WMI_SERVICE_EXT_RES_CFG_SUPPORT ; 
 int /*<<< orphan*/  WMI_SERVICE_FORCE_FW_HANG ; 
 int /*<<< orphan*/  WMI_SERVICE_HTT_MGMT_TX_COMP_VALID_FLAGS ; 
 int /*<<< orphan*/  WMI_SERVICE_IRAM_TIDS ; 
 int /*<<< orphan*/  WMI_SERVICE_MESH_11S ; 
 int /*<<< orphan*/  WMI_SERVICE_PEER_STATS ; 
 int /*<<< orphan*/  WMI_SERVICE_PER_PACKET_SW_ENCRYPT ; 
 int /*<<< orphan*/  WMI_SERVICE_PHYERR ; 
 int /*<<< orphan*/  WMI_SERVICE_RATECTRL ; 
 int /*<<< orphan*/  WMI_SERVICE_RATECTRL_CACHE ; 
 int /*<<< orphan*/  WMI_SERVICE_RESET_CHIP ; 
 int /*<<< orphan*/  WMI_SERVICE_ROAM_OFFLOAD ; 
 int /*<<< orphan*/  WMI_SERVICE_RTT ; 
 int /*<<< orphan*/  WMI_SERVICE_SCAN_OFFLOAD ; 
 int /*<<< orphan*/  WMI_SERVICE_SMART_ANTENNA_HW_SUPPORT ; 
 int /*<<< orphan*/  WMI_SERVICE_SMART_ANTENNA_SW_SUPPORT ; 
 int /*<<< orphan*/  WMI_SERVICE_STA_ADVANCED_PWRSAVE ; 
 int /*<<< orphan*/  WMI_SERVICE_STA_PWRSAVE ; 
 int /*<<< orphan*/  WMI_SERVICE_WOW ; 

__attribute__((used)) static inline void wmi_10x_svc_map(const __le32 *in, unsigned long *out,
				   size_t len)
{
	SVCMAP(WMI_10X_SERVICE_BEACON_OFFLOAD,
	       WMI_SERVICE_BEACON_OFFLOAD, len);
	SVCMAP(WMI_10X_SERVICE_SCAN_OFFLOAD,
	       WMI_SERVICE_SCAN_OFFLOAD, len);
	SVCMAP(WMI_10X_SERVICE_ROAM_OFFLOAD,
	       WMI_SERVICE_ROAM_OFFLOAD, len);
	SVCMAP(WMI_10X_SERVICE_BCN_MISS_OFFLOAD,
	       WMI_SERVICE_BCN_MISS_OFFLOAD, len);
	SVCMAP(WMI_10X_SERVICE_STA_PWRSAVE,
	       WMI_SERVICE_STA_PWRSAVE, len);
	SVCMAP(WMI_10X_SERVICE_STA_ADVANCED_PWRSAVE,
	       WMI_SERVICE_STA_ADVANCED_PWRSAVE, len);
	SVCMAP(WMI_10X_SERVICE_AP_UAPSD,
	       WMI_SERVICE_AP_UAPSD, len);
	SVCMAP(WMI_10X_SERVICE_AP_DFS,
	       WMI_SERVICE_AP_DFS, len);
	SVCMAP(WMI_10X_SERVICE_11AC,
	       WMI_SERVICE_11AC, len);
	SVCMAP(WMI_10X_SERVICE_BLOCKACK,
	       WMI_SERVICE_BLOCKACK, len);
	SVCMAP(WMI_10X_SERVICE_PHYERR,
	       WMI_SERVICE_PHYERR, len);
	SVCMAP(WMI_10X_SERVICE_BCN_FILTER,
	       WMI_SERVICE_BCN_FILTER, len);
	SVCMAP(WMI_10X_SERVICE_RTT,
	       WMI_SERVICE_RTT, len);
	SVCMAP(WMI_10X_SERVICE_RATECTRL,
	       WMI_SERVICE_RATECTRL, len);
	SVCMAP(WMI_10X_SERVICE_WOW,
	       WMI_SERVICE_WOW, len);
	SVCMAP(WMI_10X_SERVICE_RATECTRL_CACHE,
	       WMI_SERVICE_RATECTRL_CACHE, len);
	SVCMAP(WMI_10X_SERVICE_IRAM_TIDS,
	       WMI_SERVICE_IRAM_TIDS, len);
	SVCMAP(WMI_10X_SERVICE_BURST,
	       WMI_SERVICE_BURST, len);
	SVCMAP(WMI_10X_SERVICE_SMART_ANTENNA_SW_SUPPORT,
	       WMI_SERVICE_SMART_ANTENNA_SW_SUPPORT, len);
	SVCMAP(WMI_10X_SERVICE_FORCE_FW_HANG,
	       WMI_SERVICE_FORCE_FW_HANG, len);
	SVCMAP(WMI_10X_SERVICE_SMART_ANTENNA_HW_SUPPORT,
	       WMI_SERVICE_SMART_ANTENNA_HW_SUPPORT, len);
	SVCMAP(WMI_10X_SERVICE_ATF,
	       WMI_SERVICE_ATF, len);
	SVCMAP(WMI_10X_SERVICE_COEX_GPIO,
	       WMI_SERVICE_COEX_GPIO, len);
	SVCMAP(WMI_10X_SERVICE_AUX_SPECTRAL_INTF,
	       WMI_SERVICE_AUX_SPECTRAL_INTF, len);
	SVCMAP(WMI_10X_SERVICE_AUX_CHAN_LOAD_INTF,
	       WMI_SERVICE_AUX_CHAN_LOAD_INTF, len);
	SVCMAP(WMI_10X_SERVICE_BSS_CHANNEL_INFO_64,
	       WMI_SERVICE_BSS_CHANNEL_INFO_64, len);
	SVCMAP(WMI_10X_SERVICE_MESH,
	       WMI_SERVICE_MESH_11S, len);
	SVCMAP(WMI_10X_SERVICE_EXT_RES_CFG_SUPPORT,
	       WMI_SERVICE_EXT_RES_CFG_SUPPORT, len);
	SVCMAP(WMI_10X_SERVICE_PEER_STATS,
	       WMI_SERVICE_PEER_STATS, len);
	SVCMAP(WMI_10X_SERVICE_RESET_CHIP,
	       WMI_SERVICE_RESET_CHIP, len);
	SVCMAP(WMI_10X_SERVICE_HTT_MGMT_TX_COMP_VALID_FLAGS,
	       WMI_SERVICE_HTT_MGMT_TX_COMP_VALID_FLAGS, len);
	SVCMAP(WMI_10X_SERVICE_BB_TIMING_CONFIG_SUPPORT,
	       WMI_SERVICE_BB_TIMING_CONFIG_SUPPORT, len);
	SVCMAP(WMI_10X_SERVICE_PER_PACKET_SW_ENCRYPT,
	       WMI_SERVICE_PER_PACKET_SW_ENCRYPT, len);
}