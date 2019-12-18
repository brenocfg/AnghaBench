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
typedef  int /*<<< orphan*/  u32 ;
struct brcmf_vs_tlv {int dummy; } ;
struct brcmf_tlv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLV_OUI_LEN ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  WPA_OUI ; 
 int /*<<< orphan*/  WPS_OUI_TYPE ; 
 struct brcmf_tlv* brcmf_parse_tlvs (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ brcmf_tlv_has_ie (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct brcmf_vs_tlv *
brcmf_find_wpsie(const u8 *parse, u32 len)
{
	const struct brcmf_tlv *ie;

	while ((ie = brcmf_parse_tlvs(parse, len, WLAN_EID_VENDOR_SPECIFIC))) {
		if (brcmf_tlv_has_ie((u8 *)ie, &parse, &len,
				     WPA_OUI, TLV_OUI_LEN, WPS_OUI_TYPE))
			return (struct brcmf_vs_tlv *)ie;
	}
	return NULL;
}