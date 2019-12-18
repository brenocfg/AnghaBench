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
struct sk_buff {int dummy; } ;
struct mwifiex_private {int dummy; } ;
struct ieee_types_header {int dummy; } ;

/* Variables and functions */
 scalar_t__ MWIFIEX_TDLS_WMM_INFO_SIZE ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void
mwifiex_add_wmm_info_ie(struct mwifiex_private *priv, struct sk_buff *skb,
			u8 qosinfo)
{
	u8 *buf;

	buf = skb_put(skb,
		      MWIFIEX_TDLS_WMM_INFO_SIZE + sizeof(struct ieee_types_header));

	*buf++ = WLAN_EID_VENDOR_SPECIFIC;
	*buf++ = 7; /* len */
	*buf++ = 0x00; /* Microsoft OUI 00:50:F2 */
	*buf++ = 0x50;
	*buf++ = 0xf2;
	*buf++ = 2; /* WME */
	*buf++ = 0; /* WME info */
	*buf++ = 1; /* WME ver */
	*buf++ = qosinfo; /* U-APSD no in use */
}