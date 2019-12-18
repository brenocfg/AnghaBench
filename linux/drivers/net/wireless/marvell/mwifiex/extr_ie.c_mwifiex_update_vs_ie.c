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
typedef  int /*<<< orphan*/  u16 ;
struct mwifiex_ie {scalar_t__ ie_buffer; void* ie_index; void* mgmt_subtype_mask; int /*<<< orphan*/  ie_length; } ;
struct ieee_types_header {scalar_t__ len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IEEE_MAX_IE_SIZE ; 
 int /*<<< orphan*/  MWIFIEX_AUTO_IDX_MASK ; 
 int /*<<< orphan*/ * cfg80211_find_vendor_ie (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct mwifiex_ie* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_unaligned_add_cpu (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct ieee_types_header*,scalar_t__) ; 

__attribute__((used)) static int mwifiex_update_vs_ie(const u8 *ies, int ies_len,
				struct mwifiex_ie **ie_ptr, u16 mask,
				unsigned int oui, u8 oui_type)
{
	struct ieee_types_header *vs_ie;
	struct mwifiex_ie *ie = *ie_ptr;
	const u8 *vendor_ie;

	vendor_ie = cfg80211_find_vendor_ie(oui, oui_type, ies, ies_len);
	if (vendor_ie) {
		if (!*ie_ptr) {
			*ie_ptr = kzalloc(sizeof(struct mwifiex_ie),
					  GFP_KERNEL);
			if (!*ie_ptr)
				return -ENOMEM;
			ie = *ie_ptr;
		}

		vs_ie = (struct ieee_types_header *)vendor_ie;
		if (le16_to_cpu(ie->ie_length) + vs_ie->len + 2 >
			IEEE_MAX_IE_SIZE)
			return -EINVAL;
		memcpy(ie->ie_buffer + le16_to_cpu(ie->ie_length),
		       vs_ie, vs_ie->len + 2);
		le16_unaligned_add_cpu(&ie->ie_length, vs_ie->len + 2);
		ie->mgmt_subtype_mask = cpu_to_le16(mask);
		ie->ie_index = cpu_to_le16(MWIFIEX_AUTO_IDX_MASK);
	}

	*ie_ptr = ie;
	return 0;
}