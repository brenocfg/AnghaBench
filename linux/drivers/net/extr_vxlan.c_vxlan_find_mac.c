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
struct vxlan_fdb {scalar_t__ used; } ;
struct vxlan_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct vxlan_fdb* __vxlan_find_mac (struct vxlan_dev*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static struct vxlan_fdb *vxlan_find_mac(struct vxlan_dev *vxlan,
					const u8 *mac, __be32 vni)
{
	struct vxlan_fdb *f;

	f = __vxlan_find_mac(vxlan, mac, vni);
	if (f && f->used != jiffies)
		f->used = jiffies;

	return f;
}