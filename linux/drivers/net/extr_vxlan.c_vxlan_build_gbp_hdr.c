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
typedef  int /*<<< orphan*/  u32 ;
struct vxlanhdr_gbp {int dont_learn; int policy_applied; int /*<<< orphan*/  policy_id; } ;
struct vxlanhdr {int /*<<< orphan*/  vx_flags; } ;
struct vxlan_metadata {int gbp; } ;

/* Variables and functions */
 int VXLAN_GBP_DONT_LEARN ; 
 int VXLAN_GBP_ID_MASK ; 
 int VXLAN_GBP_POLICY_APPLIED ; 
 int /*<<< orphan*/  VXLAN_HF_GBP ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static void vxlan_build_gbp_hdr(struct vxlanhdr *vxh, u32 vxflags,
				struct vxlan_metadata *md)
{
	struct vxlanhdr_gbp *gbp;

	if (!md->gbp)
		return;

	gbp = (struct vxlanhdr_gbp *)vxh;
	vxh->vx_flags |= VXLAN_HF_GBP;

	if (md->gbp & VXLAN_GBP_DONT_LEARN)
		gbp->dont_learn = 1;

	if (md->gbp & VXLAN_GBP_POLICY_APPLIED)
		gbp->policy_applied = 1;

	gbp->policy_id = htons(md->gbp & VXLAN_GBP_ID_MASK);
}