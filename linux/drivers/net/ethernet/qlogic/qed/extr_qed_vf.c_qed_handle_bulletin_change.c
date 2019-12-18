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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qed_hwfn {TYPE_2__* cdev; } ;
struct qed_eth_cb_ops {int /*<<< orphan*/  (* ports_update ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* force_mac ) (void*,scalar_t__*,int) ;} ;
struct TYPE_3__ {struct qed_eth_cb_ops* eth; } ;
struct TYPE_4__ {void* ops_cookie; TYPE_1__ protocol_ops; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  qed_link_update (struct qed_hwfn*,int /*<<< orphan*/ *) ; 
 scalar_t__ qed_vf_bulletin_get_forced_mac (struct qed_hwfn*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  qed_vf_bulletin_get_udp_ports (struct qed_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_handle_bulletin_change(struct qed_hwfn *hwfn)
{
	struct qed_eth_cb_ops *ops = hwfn->cdev->protocol_ops.eth;
	u8 mac[ETH_ALEN], is_mac_exist, is_mac_forced;
	void *cookie = hwfn->cdev->ops_cookie;
	u16 vxlan_port, geneve_port;

	qed_vf_bulletin_get_udp_ports(hwfn, &vxlan_port, &geneve_port);
	is_mac_exist = qed_vf_bulletin_get_forced_mac(hwfn, mac,
						      &is_mac_forced);
	if (is_mac_exist && cookie)
		ops->force_mac(cookie, mac, !!is_mac_forced);

	ops->ports_update(cookie, vxlan_port, geneve_port);

	/* Always update link configuration according to bulletin */
	qed_link_update(hwfn, NULL);
}