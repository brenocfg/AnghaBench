#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sge {int max_ethqsets; int ethqsets; } ;
struct msix_entry {int entry; int /*<<< orphan*/  vector; } ;
struct TYPE_3__ {int nports; } ;
struct adapter {TYPE_2__* msix_info; int /*<<< orphan*/  pdev_dev; int /*<<< orphan*/  pdev; TYPE_1__ params; struct sge sge; } ;
struct TYPE_4__ {int /*<<< orphan*/  vec; } ;

/* Variables and functions */
 int MSIX_ENTRIES ; 
 int MSIX_EXTRAS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int pci_enable_msix_range (int /*<<< orphan*/ ,struct msix_entry*,int,int) ; 
 int /*<<< orphan*/  reduce_ethqs (struct adapter*,int) ; 

__attribute__((used)) static int enable_msix(struct adapter *adapter)
{
	int i, want, need, nqsets;
	struct msix_entry entries[MSIX_ENTRIES];
	struct sge *s = &adapter->sge;

	for (i = 0; i < MSIX_ENTRIES; ++i)
		entries[i].entry = i;

	/*
	 * We _want_ enough MSI-X interrupts to cover all of our "Queue Sets"
	 * plus those needed for our "extras" (for example, the firmware
	 * message queue).  We _need_ at least one "Queue Set" per Virtual
	 * Interface plus those needed for our "extras".  So now we get to see
	 * if the song is right ...
	 */
	want = s->max_ethqsets + MSIX_EXTRAS;
	need = adapter->params.nports + MSIX_EXTRAS;

	want = pci_enable_msix_range(adapter->pdev, entries, need, want);
	if (want < 0)
		return want;

	nqsets = want - MSIX_EXTRAS;
	if (nqsets < s->max_ethqsets) {
		dev_warn(adapter->pdev_dev, "only enough MSI-X vectors"
			 " for %d Queue Sets\n", nqsets);
		s->max_ethqsets = nqsets;
		if (nqsets < s->ethqsets)
			reduce_ethqs(adapter, nqsets);
	}
	for (i = 0; i < want; ++i)
		adapter->msix_info[i].vec = entries[i].vector;

	return 0;
}