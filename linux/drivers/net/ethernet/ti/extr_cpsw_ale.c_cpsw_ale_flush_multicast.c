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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int ale_entries; } ;
struct cpsw_ale {TYPE_1__ params; } ;

/* Variables and functions */
 int ALE_ENTRY_WORDS ; 
 int ALE_TYPE_ADDR ; 
 int ALE_TYPE_VLAN_ADDR ; 
 int /*<<< orphan*/  cpsw_ale_flush_mcast (struct cpsw_ale*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpsw_ale_get_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cpsw_ale_get_entry_type (int /*<<< orphan*/ *) ; 
 scalar_t__ cpsw_ale_get_mcast (int /*<<< orphan*/ *) ; 
 scalar_t__ cpsw_ale_get_super (int /*<<< orphan*/ *) ; 
 int cpsw_ale_get_vlan_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpsw_ale_read (struct cpsw_ale*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpsw_ale_write (struct cpsw_ale*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/ *) ; 

int cpsw_ale_flush_multicast(struct cpsw_ale *ale, int port_mask, int vid)
{
	u32 ale_entry[ALE_ENTRY_WORDS];
	int ret, idx;

	for (idx = 0; idx < ale->params.ale_entries; idx++) {
		cpsw_ale_read(ale, idx, ale_entry);
		ret = cpsw_ale_get_entry_type(ale_entry);
		if (ret != ALE_TYPE_ADDR && ret != ALE_TYPE_VLAN_ADDR)
			continue;

		/* if vid passed is -1 then remove all multicast entry from
		 * the table irrespective of vlan id, if a valid vlan id is
		 * passed then remove only multicast added to that vlan id.
		 * if vlan id doesn't match then move on to next entry.
		 */
		if (vid != -1 && cpsw_ale_get_vlan_id(ale_entry) != vid)
			continue;

		if (cpsw_ale_get_mcast(ale_entry)) {
			u8 addr[6];

			if (cpsw_ale_get_super(ale_entry))
				continue;

			cpsw_ale_get_addr(ale_entry, addr);
			if (!is_broadcast_ether_addr(addr))
				cpsw_ale_flush_mcast(ale, ale_entry, port_mask);
		}

		cpsw_ale_write(ale, idx, ale_entry);
	}
	return 0;
}