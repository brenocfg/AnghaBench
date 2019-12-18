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
typedef  int /*<<< orphan*/  unicst_pattern ;
typedef  int u8 ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;
typedef  int /*<<< orphan*/  discvr_pattern ;
typedef  int /*<<< orphan*/  dhcp_pattern ;
typedef  int /*<<< orphan*/  arp_pattern ;

/* Variables and functions */
 int /*<<< orphan*/  WOW_LIST_ID ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 int ath6kl_wmi_add_wow_pattern_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int const*,int const*) ; 

__attribute__((used)) static int ath6kl_wow_ap(struct ath6kl *ar, struct ath6kl_vif *vif)
{
	static const u8 unicst_pattern[] = { 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x08 };
	static const u8 unicst_mask[] = { 0x01, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x7f };
	u8 unicst_offset = 0;
	static const u8 arp_pattern[] = { 0x08, 0x06 };
	static const u8 arp_mask[] = { 0xff, 0xff };
	u8 arp_offset = 20;
	static const u8 discvr_pattern[] = { 0xe0, 0x00, 0x00, 0xf8 };
	static const u8 discvr_mask[] = { 0xf0, 0x00, 0x00, 0xf8 };
	u8 discvr_offset = 38;
	static const u8 dhcp_pattern[] = { 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x43 /* port 67 */ };
	static const u8 dhcp_mask[] = { 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0xff, 0xff /* port 67 */ };
	u8 dhcp_offset = 0;
	int ret;

	/* Setup unicast IP, EAPOL-like and ARP pkt pattern */
	ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
			vif->fw_vif_idx, WOW_LIST_ID,
			sizeof(unicst_pattern), unicst_offset,
			unicst_pattern, unicst_mask);
	if (ret) {
		ath6kl_err("failed to add WOW unicast IP pattern\n");
		return ret;
	}

	/* Setup all ARP pkt pattern */
	ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
			vif->fw_vif_idx, WOW_LIST_ID,
			sizeof(arp_pattern), arp_offset,
			arp_pattern, arp_mask);
	if (ret) {
		ath6kl_err("failed to add WOW ARP pattern\n");
		return ret;
	}

	/*
	 * Setup multicast pattern for mDNS 224.0.0.251,
	 * SSDP 239.255.255.250 and LLMNR  224.0.0.252
	 */
	ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
			vif->fw_vif_idx, WOW_LIST_ID,
			sizeof(discvr_pattern), discvr_offset,
			discvr_pattern, discvr_mask);
	if (ret) {
		ath6kl_err("failed to add WOW mDNS/SSDP/LLMNR pattern\n");
		return ret;
	}

	/* Setup all DHCP broadcast pkt pattern */
	ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
			vif->fw_vif_idx, WOW_LIST_ID,
			sizeof(dhcp_pattern), dhcp_offset,
			dhcp_pattern, dhcp_mask);
	if (ret) {
		ath6kl_err("failed to add WOW DHCP broadcast pattern\n");
		return ret;
	}

	return 0;
}