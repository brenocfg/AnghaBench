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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  device_capabilities; } ;
struct qed_hwfn {TYPE_1__ hw_info; } ;
typedef  enum qed_pci_personality { ____Placeholder_qed_pci_personality } qed_pci_personality ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int /*<<< orphan*/  QED_DEV_CAP_ROCE ; 
 int QED_PCI_ETH ; 
 int QED_PCI_ETH_ROCE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qed_mcp_get_shmem_proto_legacy(struct qed_hwfn *p_hwfn,
			       enum qed_pci_personality *p_proto)
{
	/* There wasn't ever a legacy MFW that published iwarp.
	 * So at this point, this is either plain l2 or RoCE.
	 */
	if (test_bit(QED_DEV_CAP_ROCE, &p_hwfn->hw_info.device_capabilities))
		*p_proto = QED_PCI_ETH_ROCE;
	else
		*p_proto = QED_PCI_ETH;

	DP_VERBOSE(p_hwfn, NETIF_MSG_IFUP,
		   "According to Legacy capabilities, L2 personality is %08x\n",
		   (u32) *p_proto);
}