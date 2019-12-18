#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u8 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  const* variable; } ;
struct TYPE_4__ {TYPE_1__ beacon; } ;
struct ieee80211_mgmt {TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  const* cfg80211_find_ie (int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static u32 iwl_mvm_find_ie_offset(u8 *beacon, u8 eid, u32 frame_size)
{
	struct ieee80211_mgmt *mgmt = (void *)beacon;
	const u8 *ie;

	if (WARN_ON_ONCE(frame_size <= (mgmt->u.beacon.variable - beacon)))
		return 0;

	frame_size -= mgmt->u.beacon.variable - beacon;

	ie = cfg80211_find_ie(eid, mgmt->u.beacon.variable, frame_size);
	if (!ie)
		return 0;

	return ie - beacon;
}