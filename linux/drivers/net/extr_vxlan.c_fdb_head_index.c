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
struct TYPE_2__ {int flags; } ;
struct vxlan_dev {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int VXLAN_F_COLLECT_METADATA ; 
 int /*<<< orphan*/  eth_hash (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eth_vni_hash (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 fdb_head_index(struct vxlan_dev *vxlan, const u8 *mac, __be32 vni)
{
	if (vxlan->cfg.flags & VXLAN_F_COLLECT_METADATA)
		return eth_vni_hash(mac, vni);
	else
		return eth_hash(mac);
}