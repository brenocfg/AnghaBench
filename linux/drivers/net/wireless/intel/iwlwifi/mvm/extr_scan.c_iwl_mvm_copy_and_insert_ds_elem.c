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
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WLAN_EID_DS_PARAMS ; 
#define  WLAN_EID_EXT_SUPP_RATES 131 
#define  WLAN_EID_REQUEST 130 
#define  WLAN_EID_SSID 129 
#define  WLAN_EID_SUPP_RATES 128 
 size_t ieee80211_ie_split (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_rrm_scan_needed (struct iwl_mvm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static u8 *iwl_mvm_copy_and_insert_ds_elem(struct iwl_mvm *mvm, const u8 *ies,
					   size_t len, u8 *const pos)
{
	static const u8 before_ds_params[] = {
			WLAN_EID_SSID,
			WLAN_EID_SUPP_RATES,
			WLAN_EID_REQUEST,
			WLAN_EID_EXT_SUPP_RATES,
	};
	size_t offs;
	u8 *newpos = pos;

	if (!iwl_mvm_rrm_scan_needed(mvm)) {
		memcpy(newpos, ies, len);
		return newpos + len;
	}

	offs = ieee80211_ie_split(ies, len,
				  before_ds_params,
				  ARRAY_SIZE(before_ds_params),
				  0);

	memcpy(newpos, ies, offs);
	newpos += offs;

	/* Add a placeholder for DS Parameter Set element */
	*newpos++ = WLAN_EID_DS_PARAMS;
	*newpos++ = 1;
	*newpos++ = 0;

	memcpy(newpos, ies + offs, len - offs);
	newpos += len - offs;

	return newpos;
}