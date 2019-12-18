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
typedef  size_t u32 ;
struct vxlan_fdb {int dummy; } ;
struct vxlan_dev {int /*<<< orphan*/ * hash_lock; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct vxlan_fdb* __vxlan_find_mac (struct vxlan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_zeros_mac ; 
 size_t fdb_head_index (struct vxlan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxlan_fdb_destroy (struct vxlan_dev*,struct vxlan_fdb*,int,int) ; 

__attribute__((used)) static void vxlan_fdb_delete_default(struct vxlan_dev *vxlan, __be32 vni)
{
	struct vxlan_fdb *f;
	u32 hash_index = fdb_head_index(vxlan, all_zeros_mac, vni);

	spin_lock_bh(&vxlan->hash_lock[hash_index]);
	f = __vxlan_find_mac(vxlan, all_zeros_mac, vni);
	if (f)
		vxlan_fdb_destroy(vxlan, f, true, true);
	spin_unlock_bh(&vxlan->hash_lock[hash_index]);
}