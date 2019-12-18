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
typedef  int /*<<< orphan*/  u8 ;
struct mt7615_vif {int omac_idx; } ;
struct bss_info_ext_bss {int /*<<< orphan*/  mbss_tsf_offset; void* len; void* tag; } ;

/* Variables and functions */
 int BCN_TX_ESTIMATE_TIME ; 
 int BSS_INFO_EXT_BSS ; 
 int EXT_BSSID_START ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static void
mt7615_mcu_bss_info_ext_header(struct mt7615_vif *mvif, u8 *data)
{
/* SIFS 20us + 512 byte beacon tranmitted by 1Mbps (3906us) */
#define BCN_TX_ESTIMATE_TIME (4096 + 20)
	struct bss_info_ext_bss *hdr = (struct bss_info_ext_bss *)data;
	int ext_bss_idx, tsf_offset;

	ext_bss_idx = mvif->omac_idx - EXT_BSSID_START;
	if (ext_bss_idx < 0)
		return;

	hdr->tag = cpu_to_le16(BSS_INFO_EXT_BSS);
	hdr->len = cpu_to_le16(sizeof(struct bss_info_ext_bss));
	tsf_offset = ext_bss_idx * BCN_TX_ESTIMATE_TIME;
	hdr->mbss_tsf_offset = cpu_to_le32(tsf_offset);
}