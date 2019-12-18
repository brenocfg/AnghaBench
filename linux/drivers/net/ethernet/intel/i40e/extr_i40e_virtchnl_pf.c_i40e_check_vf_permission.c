#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct virtchnl_ether_addr_list {int num_elements; TYPE_1__* list; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct i40e_vf {scalar_t__ num_mac; TYPE_2__ default_lan_addr; scalar_t__ pf_set_mac; int /*<<< orphan*/  vf_caps; struct i40e_pf* pf; } ;
struct i40e_pf {TYPE_3__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int EPERM ; 
 int I40E_ERR_INVALID_MAC_ADDR ; 
 scalar_t__ I40E_VC_MAX_MAC_ADDR_PER_VF ; 
 int /*<<< orphan*/  I40E_VIRTCHNL_VF_CAP_PRIVILEGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int i40e_check_vf_permission(struct i40e_vf *vf,
					   struct virtchnl_ether_addr_list *al)
{
	struct i40e_pf *pf = vf->pf;
	int i;

	/* If this VF is not privileged, then we can't add more than a limited
	 * number of addresses. Check to make sure that the additions do not
	 * push us over the limit.
	 */
	if (!test_bit(I40E_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps) &&
	    (vf->num_mac + al->num_elements) > I40E_VC_MAX_MAC_ADDR_PER_VF) {
		dev_err(&pf->pdev->dev,
			"Cannot add more MAC addresses, VF is not trusted, switch the VF to trusted to add more functionality\n");
		return -EPERM;
	}

	for (i = 0; i < al->num_elements; i++) {
		u8 *addr = al->list[i].addr;

		if (is_broadcast_ether_addr(addr) ||
		    is_zero_ether_addr(addr)) {
			dev_err(&pf->pdev->dev, "invalid VF MAC addr %pM\n",
				addr);
			return I40E_ERR_INVALID_MAC_ADDR;
		}

		/* If the host VMM administrator has set the VF MAC address
		 * administratively via the ndo_set_vf_mac command then deny
		 * permission to the VF to add or delete unicast MAC addresses.
		 * Unless the VF is privileged and then it can do whatever.
		 * The VF may request to set the MAC address filter already
		 * assigned to it so do not return an error in that case.
		 */
		if (!test_bit(I40E_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps) &&
		    !is_multicast_ether_addr(addr) && vf->pf_set_mac &&
		    !ether_addr_equal(addr, vf->default_lan_addr.addr)) {
			dev_err(&pf->pdev->dev,
				"VF attempting to override administratively set MAC address, bring down and up the VF interface to resume normal operation\n");
			return -EPERM;
		}
	}

	return 0;
}