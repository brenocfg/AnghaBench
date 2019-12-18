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
struct vxlan_fdb {int /*<<< orphan*/  eth_addr; int /*<<< orphan*/  remotes; int /*<<< orphan*/  vni; int /*<<< orphan*/  used; int /*<<< orphan*/  updated; void* flags; void* state; } ;
struct vxlan_dev {int dummy; } ;
typedef  void* __u16 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct vxlan_fdb* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vxlan_fdb *vxlan_fdb_alloc(struct vxlan_dev *vxlan,
					 const u8 *mac, __u16 state,
					 __be32 src_vni, __u16 ndm_flags)
{
	struct vxlan_fdb *f;

	f = kmalloc(sizeof(*f), GFP_ATOMIC);
	if (!f)
		return NULL;
	f->state = state;
	f->flags = ndm_flags;
	f->updated = f->used = jiffies;
	f->vni = src_vni;
	INIT_LIST_HEAD(&f->remotes);
	memcpy(f->eth_addr, mac, ETH_ALEN);

	return f;
}