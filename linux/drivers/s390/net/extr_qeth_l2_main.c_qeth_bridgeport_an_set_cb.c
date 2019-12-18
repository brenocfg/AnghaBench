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
struct qeth_card {int dummy; } ;
struct TYPE_2__ {scalar_t__ lnid; } ;
struct qdio_brinfo_entry_l2 {TYPE_1__ addr_lnid; int /*<<< orphan*/  nit; } ;
struct net_if_token {int dummy; } ;
struct mac_addr_lnid {int dummy; } ;
typedef  enum qdio_brinfo_entry_type { ____Placeholder_qdio_brinfo_entry_type } qdio_brinfo_entry_type ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_ADDR_CHANGE_CODE_MACADDR ; 
 int /*<<< orphan*/  IPA_ADDR_CHANGE_CODE_VLANID ; 
 scalar_t__ VLAN_N_VID ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  anev_reg_unreg ; 
 int l2_addr_lnid ; 
 int /*<<< orphan*/  qeth_bridge_emit_host_event (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_if_token*,struct mac_addr_lnid*) ; 

__attribute__((used)) static void qeth_bridgeport_an_set_cb(void *priv,
		enum qdio_brinfo_entry_type type, void *entry)
{
	struct qeth_card *card = (struct qeth_card *)priv;
	struct qdio_brinfo_entry_l2 *l2entry;
	u8 code;

	if (type != l2_addr_lnid) {
		WARN_ON_ONCE(1);
		return;
	}

	l2entry = (struct qdio_brinfo_entry_l2 *)entry;
	code = IPA_ADDR_CHANGE_CODE_MACADDR;
	if (l2entry->addr_lnid.lnid < VLAN_N_VID)
		code |= IPA_ADDR_CHANGE_CODE_VLANID;
	qeth_bridge_emit_host_event(card, anev_reg_unreg, code,
		(struct net_if_token *)&l2entry->nit,
		(struct mac_addr_lnid *)&l2entry->addr_lnid);
}