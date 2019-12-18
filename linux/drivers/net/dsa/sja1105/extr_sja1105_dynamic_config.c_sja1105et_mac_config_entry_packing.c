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
struct sja1105_mac_config_entry {int /*<<< orphan*/  tp_delout; int /*<<< orphan*/  tp_delin; int /*<<< orphan*/  vlanid; int /*<<< orphan*/  vlanprio; int /*<<< orphan*/  egr_mirr; int /*<<< orphan*/  ing_mirr; int /*<<< orphan*/  ingress; int /*<<< orphan*/  egress; int /*<<< orphan*/  dyn_learn; int /*<<< orphan*/  retag; int /*<<< orphan*/  drpuntag; int /*<<< orphan*/  drpdtag; int /*<<< orphan*/  speed; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 int SJA1105ET_SIZE_MAC_CONFIG_DYN_ENTRY ; 
 int /*<<< orphan*/  sja1105_packing (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int const,int) ; 

__attribute__((used)) static size_t sja1105et_mac_config_entry_packing(void *buf, void *entry_ptr,
						 enum packing_op op)
{
	const int size = SJA1105ET_SIZE_MAC_CONFIG_DYN_ENTRY;
	struct sja1105_mac_config_entry *entry = entry_ptr;
	/* Yup, user manual definitions are reversed */
	u8 *reg1 = buf + 4;
	u8 *reg2 = buf;

	sja1105_packing(reg1, &entry->speed,     30, 29, size, op);
	sja1105_packing(reg1, &entry->drpdtag,   23, 23, size, op);
	sja1105_packing(reg1, &entry->drpuntag,  22, 22, size, op);
	sja1105_packing(reg1, &entry->retag,     21, 21, size, op);
	sja1105_packing(reg1, &entry->dyn_learn, 20, 20, size, op);
	sja1105_packing(reg1, &entry->egress,    19, 19, size, op);
	sja1105_packing(reg1, &entry->ingress,   18, 18, size, op);
	sja1105_packing(reg1, &entry->ing_mirr,  17, 17, size, op);
	sja1105_packing(reg1, &entry->egr_mirr,  16, 16, size, op);
	sja1105_packing(reg1, &entry->vlanprio,  14, 12, size, op);
	sja1105_packing(reg1, &entry->vlanid,    11,  0, size, op);
	sja1105_packing(reg2, &entry->tp_delin,  31, 16, size, op);
	sja1105_packing(reg2, &entry->tp_delout, 15,  0, size, op);
	/* MAC configuration table entries which can't be reconfigured:
	 * top, base, enabled, ifg, maxage, drpnona664
	 */
	/* Bogus return value, not used anywhere */
	return 0;
}