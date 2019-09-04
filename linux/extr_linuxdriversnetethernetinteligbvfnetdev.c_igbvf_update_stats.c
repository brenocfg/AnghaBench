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
struct pci_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  mprc; } ;
struct e1000_hw {int dummy; } ;
struct igbvf_adapter {scalar_t__ link_speed; TYPE_3__ stats; TYPE_2__* netdev; int /*<<< orphan*/  state; struct pci_dev* pdev; struct e1000_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  multicast; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPDATE_VF_COUNTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFGORC ; 
 int /*<<< orphan*/  VFGORLBC ; 
 int /*<<< orphan*/  VFGOTC ; 
 int /*<<< orphan*/  VFGOTLBC ; 
 int /*<<< orphan*/  VFGPRC ; 
 int /*<<< orphan*/  VFGPRLBC ; 
 int /*<<< orphan*/  VFGPTC ; 
 int /*<<< orphan*/  VFGPTLBC ; 
 int /*<<< orphan*/  VFMPRC ; 
 int /*<<< orphan*/  __IGBVF_RESETTING ; 
 int /*<<< orphan*/  gorc ; 
 int /*<<< orphan*/  gorlbc ; 
 int /*<<< orphan*/  gotc ; 
 int /*<<< orphan*/  gotlbc ; 
 int /*<<< orphan*/  gprc ; 
 int /*<<< orphan*/  gprlbc ; 
 int /*<<< orphan*/  gptc ; 
 int /*<<< orphan*/  gptlbc ; 
 int /*<<< orphan*/  mprc ; 
 scalar_t__ pci_channel_offline (struct pci_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void igbvf_update_stats(struct igbvf_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct pci_dev *pdev = adapter->pdev;

	/* Prevent stats update while adapter is being reset, link is down
	 * or if the pci connection is down.
	 */
	if (adapter->link_speed == 0)
		return;

	if (test_bit(__IGBVF_RESETTING, &adapter->state))
		return;

	if (pci_channel_offline(pdev))
		return;

	UPDATE_VF_COUNTER(VFGPRC, gprc);
	UPDATE_VF_COUNTER(VFGORC, gorc);
	UPDATE_VF_COUNTER(VFGPTC, gptc);
	UPDATE_VF_COUNTER(VFGOTC, gotc);
	UPDATE_VF_COUNTER(VFMPRC, mprc);
	UPDATE_VF_COUNTER(VFGOTLBC, gotlbc);
	UPDATE_VF_COUNTER(VFGPTLBC, gptlbc);
	UPDATE_VF_COUNTER(VFGORLBC, gorlbc);
	UPDATE_VF_COUNTER(VFGPRLBC, gprlbc);

	/* Fill out the OS statistics structure */
	adapter->netdev->stats.multicast = adapter->stats.mprc;
}