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
typedef  union vxlan_addr {int dummy; } vxlan_addr ;
typedef  int /*<<< orphan*/  u32 ;
struct vxlan_rdst {int dummy; } ;
struct vxlan_fdb {int /*<<< orphan*/  remotes; } ;
struct vxlan_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxlan_addr_any (union vxlan_addr*) ; 
 int /*<<< orphan*/  vxlan_fdb_destroy (struct vxlan_dev*,struct vxlan_fdb*,int,int) ; 
 int /*<<< orphan*/  vxlan_fdb_dst_destroy (struct vxlan_dev*,struct vxlan_fdb*,struct vxlan_rdst*,int) ; 
 struct vxlan_rdst* vxlan_fdb_find_rdst (struct vxlan_fdb*,union vxlan_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vxlan_fdb* vxlan_find_mac (struct vxlan_dev*,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __vxlan_fdb_delete(struct vxlan_dev *vxlan,
			      const unsigned char *addr, union vxlan_addr ip,
			      __be16 port, __be32 src_vni, __be32 vni,
			      u32 ifindex, bool swdev_notify)
{
	struct vxlan_fdb *f;
	struct vxlan_rdst *rd = NULL;
	int err = -ENOENT;

	f = vxlan_find_mac(vxlan, addr, src_vni);
	if (!f)
		return err;

	if (!vxlan_addr_any(&ip)) {
		rd = vxlan_fdb_find_rdst(f, &ip, port, vni, ifindex);
		if (!rd)
			goto out;
	}

	/* remove a destination if it's not the only one on the list,
	 * otherwise destroy the fdb entry
	 */
	if (rd && !list_is_singular(&f->remotes)) {
		vxlan_fdb_dst_destroy(vxlan, f, rd, swdev_notify);
		goto out;
	}

	vxlan_fdb_destroy(vxlan, f, true, swdev_notify);

out:
	return 0;
}