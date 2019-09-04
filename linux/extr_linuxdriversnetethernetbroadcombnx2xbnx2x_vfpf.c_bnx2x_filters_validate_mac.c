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
struct vfpf_set_q_filters_tlv {int n_mac_vlan_filters; struct vfpf_q_mac_vlan_filter* filters; } ;
struct vfpf_q_mac_vlan_filter {int flags; int /*<<< orphan*/  mac; } ;
struct pf_vf_bulletin_content {int valid_bitmap; int /*<<< orphan*/  mac; } ;
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; int /*<<< orphan*/  index; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,...) ; 
 struct pf_vf_bulletin_content* BP_VF_BULLETIN (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int EPERM ; 
 int MAC_ADDR_VALID ; 
 int VFPF_Q_FILTER_DEST_MAC_VALID ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_filters_validate_mac(struct bnx2x *bp,
				      struct bnx2x_virtf *vf,
				      struct vfpf_set_q_filters_tlv *filters)
{
	struct pf_vf_bulletin_content *bulletin = BP_VF_BULLETIN(bp, vf->index);
	int rc = 0;

	/* if a mac was already set for this VF via the set vf mac ndo, we only
	 * accept mac configurations of that mac. Why accept them at all?
	 * because PF may have been unable to configure the mac at the time
	 * since queue was not set up.
	 */
	if (bulletin->valid_bitmap & 1 << MAC_ADDR_VALID) {
		struct vfpf_q_mac_vlan_filter *filter = NULL;
		int i;

		for (i = 0; i < filters->n_mac_vlan_filters; i++) {
			if (!(filters->filters[i].flags &
			      VFPF_Q_FILTER_DEST_MAC_VALID))
				continue;

			/* once a mac was set by ndo can only accept
			 * a single mac...
			 */
			if (filter) {
				BNX2X_ERR("VF[%d] requested the addition of multiple macs after set_vf_mac ndo was called [%d filters]\n",
					  vf->abs_vfid,
					  filters->n_mac_vlan_filters);
				rc = -EPERM;
				goto response;
			}

			filter = &filters->filters[i];
		}

		/* ...and only the mac set by the ndo */
		if (filter &&
		    !ether_addr_equal(filter->mac, bulletin->mac)) {
			BNX2X_ERR("VF[%d] requested the addition of a mac address not matching the one configured by set_vf_mac ndo\n",
				  vf->abs_vfid);

			rc = -EPERM;
			goto response;
		}
	}

response:
	return rc;
}