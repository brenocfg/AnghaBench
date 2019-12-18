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
typedef  int /*<<< orphan*/  wps_oui ;
typedef  int /*<<< orphan*/  wpa_oui ;
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int session_enable; } ;
struct mwifiex_private {int gen_ie_buf_len; scalar_t__ gen_ie_buf; int /*<<< orphan*/  adapter; TYPE_1__ wps; } ;
struct ieee_types_vendor_header {int len; scalar_t__ element_id; int /*<<< orphan*/  oui; } ;
struct ieee_types_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG ; 
 scalar_t__ WLAN_EID_BSS_AC_ACCESS_DELAY ; 
 scalar_t__ WLAN_EID_RSN ; 
 scalar_t__ WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_set_wapi_ie (struct mwifiex_private*,int*,int) ; 
 int /*<<< orphan*/  mwifiex_set_wpa_ie (struct mwifiex_private*,int*,int) ; 
 int /*<<< orphan*/  mwifiex_set_wps_ie (struct mwifiex_private*,int*,int) ; 

__attribute__((used)) static int
mwifiex_set_gen_ie_helper(struct mwifiex_private *priv, u8 *ie_data_ptr,
			  u16 ie_len)
{
	struct ieee_types_vendor_header *pvendor_ie;
	const u8 wpa_oui[] = { 0x00, 0x50, 0xf2, 0x01 };
	const u8 wps_oui[] = { 0x00, 0x50, 0xf2, 0x04 };
	u16 unparsed_len = ie_len, cur_ie_len;

	/* If the passed length is zero, reset the buffer */
	if (!ie_len) {
		priv->gen_ie_buf_len = 0;
		priv->wps.session_enable = false;
		return 0;
	} else if (!ie_data_ptr ||
		   ie_len <= sizeof(struct ieee_types_header)) {
		return -1;
	}
	pvendor_ie = (struct ieee_types_vendor_header *) ie_data_ptr;

	while (pvendor_ie) {
		cur_ie_len = pvendor_ie->len + sizeof(struct ieee_types_header);

		if (pvendor_ie->element_id == WLAN_EID_RSN) {
			/* IE is a WPA/WPA2 IE so call set_wpa function */
			mwifiex_set_wpa_ie(priv, (u8 *)pvendor_ie, cur_ie_len);
			priv->wps.session_enable = false;
			goto next_ie;
		}

		if (pvendor_ie->element_id == WLAN_EID_BSS_AC_ACCESS_DELAY) {
			/* IE is a WAPI IE so call set_wapi function */
			mwifiex_set_wapi_ie(priv, (u8 *)pvendor_ie,
					    cur_ie_len);
			goto next_ie;
		}

		if (pvendor_ie->element_id == WLAN_EID_VENDOR_SPECIFIC) {
			/* Test to see if it is a WPA IE, if not, then
			 * it is a gen IE
			 */
			if (!memcmp(&pvendor_ie->oui, wpa_oui,
				    sizeof(wpa_oui))) {
				/* IE is a WPA/WPA2 IE so call set_wpa function
				 */
				mwifiex_set_wpa_ie(priv, (u8 *)pvendor_ie,
						   cur_ie_len);
				priv->wps.session_enable = false;
				goto next_ie;
			}

			if (!memcmp(&pvendor_ie->oui, wps_oui,
				    sizeof(wps_oui))) {
				/* Test to see if it is a WPS IE,
				 * if so, enable wps session flag
				 */
				priv->wps.session_enable = true;
				mwifiex_dbg(priv->adapter, MSG,
					    "WPS Session Enabled.\n");
				mwifiex_set_wps_ie(priv, (u8 *)pvendor_ie,
						   cur_ie_len);
				goto next_ie;
			}
		}

		/* Saved in gen_ie, such as P2P IE.etc.*/

		/* Verify that the passed length is not larger than the
		 * available space remaining in the buffer
		 */
		if (cur_ie_len <
		    (sizeof(priv->gen_ie_buf) - priv->gen_ie_buf_len)) {
			/* Append the passed data to the end
			 * of the genIeBuffer
			 */
			memcpy(priv->gen_ie_buf + priv->gen_ie_buf_len,
			       (u8 *)pvendor_ie, cur_ie_len);
			/* Increment the stored buffer length by the
			 * size passed
			 */
			priv->gen_ie_buf_len += cur_ie_len;
		}

next_ie:
		unparsed_len -= cur_ie_len;

		if (unparsed_len <= sizeof(struct ieee_types_header))
			pvendor_ie = NULL;
		else
			pvendor_ie = (struct ieee_types_vendor_header *)
				(((u8 *)pvendor_ie) + cur_ie_len);
	}

	return 0;
}