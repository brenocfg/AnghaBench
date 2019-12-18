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
 int /*<<< orphan*/  SVCMAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_SERVICE_SPOOF_MAC_SUPPORT ; 
 int /*<<< orphan*/  WMI_SERVICE_THERM_THROT ; 
 int /*<<< orphan*/  WMI_SERVICE_TX_DATA_ACK_RSSI ; 
 int /*<<< orphan*/  WMI_TLV_MAX_SERVICE ; 
 int /*<<< orphan*/  WMI_TLV_SERVICE_SPOOF_MAC_SUPPORT ; 
 int /*<<< orphan*/  WMI_TLV_SERVICE_THERM_THROT ; 
 int /*<<< orphan*/  WMI_TLV_SERVICE_TX_DATA_MGMT_ACK_RSSI ; 

__attribute__((used)) static inline void
wmi_tlv_svc_map_ext(const __le32 *in, unsigned long *out, size_t len)
{
	SVCMAP(WMI_TLV_SERVICE_SPOOF_MAC_SUPPORT,
	       WMI_SERVICE_SPOOF_MAC_SUPPORT,
	       WMI_TLV_MAX_SERVICE);
	SVCMAP(WMI_TLV_SERVICE_THERM_THROT,
	       WMI_SERVICE_THERM_THROT,
	       WMI_TLV_MAX_SERVICE);
	SVCMAP(WMI_TLV_SERVICE_TX_DATA_MGMT_ACK_RSSI,
	       WMI_SERVICE_TX_DATA_ACK_RSSI, WMI_TLV_MAX_SERVICE);
}