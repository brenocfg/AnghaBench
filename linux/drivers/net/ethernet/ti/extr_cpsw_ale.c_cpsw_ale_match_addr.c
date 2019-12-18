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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int ale_entries; } ;
struct cpsw_ale {TYPE_1__ params; } ;

/* Variables and functions */
 int ALE_ENTRY_WORDS ; 
 int ALE_TYPE_ADDR ; 
 int ALE_TYPE_VLAN_ADDR ; 
 int ENOENT ; 
 int /*<<< orphan*/  cpsw_ale_get_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cpsw_ale_get_entry_type (int /*<<< orphan*/ *) ; 
 scalar_t__ cpsw_ale_get_vlan_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpsw_ale_read (struct cpsw_ale*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int cpsw_ale_match_addr(struct cpsw_ale *ale, const u8 *addr, u16 vid)
{
	u32 ale_entry[ALE_ENTRY_WORDS];
	int type, idx;

	for (idx = 0; idx < ale->params.ale_entries; idx++) {
		u8 entry_addr[6];

		cpsw_ale_read(ale, idx, ale_entry);
		type = cpsw_ale_get_entry_type(ale_entry);
		if (type != ALE_TYPE_ADDR && type != ALE_TYPE_VLAN_ADDR)
			continue;
		if (cpsw_ale_get_vlan_id(ale_entry) != vid)
			continue;
		cpsw_ale_get_addr(ale_entry, entry_addr);
		if (ether_addr_equal(entry_addr, addr))
			return idx;
	}
	return -ENOENT;
}