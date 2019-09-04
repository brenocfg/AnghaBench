#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sge {int max_ethqsets; int ofldqsets; int ethqsets; unsigned int nqs_per_uld; } ;
struct msix_entry {int entry; int /*<<< orphan*/  vector; } ;
struct TYPE_8__ {int mapsize; } ;
struct TYPE_5__ {unsigned int nports; scalar_t__ crypto; scalar_t__ offload; } ;
struct adapter {int num_uld; int num_ofld_uld; int /*<<< orphan*/  pdev_dev; TYPE_4__ msix_bmap_ulds; TYPE_3__* msix_info_ulds; TYPE_2__* msix_info; int /*<<< orphan*/  pdev; TYPE_1__ params; struct sge sge; } ;
struct TYPE_7__ {int idx; int /*<<< orphan*/  vec; } ;
struct TYPE_6__ {int /*<<< orphan*/  vec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EXTRA_VECS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_INGQ ; 
 int MAX_OFLD_QSETS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_msix_info (struct adapter*) ; 
 scalar_t__ is_offload (struct adapter*) ; 
 scalar_t__ is_pci_uld (struct adapter*) ; 
 scalar_t__ is_uld (struct adapter*) ; 
 int /*<<< orphan*/  kfree (struct msix_entry*) ; 
 struct msix_entry* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int pci_enable_msix_range (int /*<<< orphan*/ ,struct msix_entry*,int,int) ; 
 int /*<<< orphan*/  reduce_ethqs (struct adapter*,int) ; 

__attribute__((used)) static int enable_msix(struct adapter *adap)
{
	int ofld_need = 0, uld_need = 0;
	int i, j, want, need, allocated;
	struct sge *s = &adap->sge;
	unsigned int nchan = adap->params.nports;
	struct msix_entry *entries;
	int max_ingq = MAX_INGQ;

	if (is_pci_uld(adap))
		max_ingq += (MAX_OFLD_QSETS * adap->num_uld);
	if (is_offload(adap))
		max_ingq += (MAX_OFLD_QSETS * adap->num_ofld_uld);
	entries = kmalloc_array(max_ingq + 1, sizeof(*entries),
				GFP_KERNEL);
	if (!entries)
		return -ENOMEM;

	/* map for msix */
	if (get_msix_info(adap)) {
		adap->params.offload = 0;
		adap->params.crypto = 0;
	}

	for (i = 0; i < max_ingq + 1; ++i)
		entries[i].entry = i;

	want = s->max_ethqsets + EXTRA_VECS;
	if (is_offload(adap)) {
		want += adap->num_ofld_uld * s->ofldqsets;
		ofld_need = adap->num_ofld_uld * nchan;
	}
	if (is_pci_uld(adap)) {
		want += adap->num_uld * s->ofldqsets;
		uld_need = adap->num_uld * nchan;
	}
#ifdef CONFIG_CHELSIO_T4_DCB
	/* For Data Center Bridging we need 8 Ethernet TX Priority Queues for
	 * each port.
	 */
	need = 8 * adap->params.nports + EXTRA_VECS + ofld_need + uld_need;
#else
	need = adap->params.nports + EXTRA_VECS + ofld_need + uld_need;
#endif
	allocated = pci_enable_msix_range(adap->pdev, entries, need, want);
	if (allocated < 0) {
		dev_info(adap->pdev_dev, "not enough MSI-X vectors left,"
			 " not using MSI-X\n");
		kfree(entries);
		return allocated;
	}

	/* Distribute available vectors to the various queue groups.
	 * Every group gets its minimum requirement and NIC gets top
	 * priority for leftovers.
	 */
	i = allocated - EXTRA_VECS - ofld_need - uld_need;
	if (i < s->max_ethqsets) {
		s->max_ethqsets = i;
		if (i < s->ethqsets)
			reduce_ethqs(adap, i);
	}
	if (is_uld(adap)) {
		if (allocated < want)
			s->nqs_per_uld = nchan;
		else
			s->nqs_per_uld = s->ofldqsets;
	}

	for (i = 0; i < (s->max_ethqsets + EXTRA_VECS); ++i)
		adap->msix_info[i].vec = entries[i].vector;
	if (is_uld(adap)) {
		for (j = 0 ; i < allocated; ++i, j++) {
			adap->msix_info_ulds[j].vec = entries[i].vector;
			adap->msix_info_ulds[j].idx = i;
		}
		adap->msix_bmap_ulds.mapsize = j;
	}
	dev_info(adap->pdev_dev, "%d MSI-X vectors allocated, "
		 "nic %d per uld %d\n",
		 allocated, s->max_ethqsets, s->nqs_per_uld);

	kfree(entries);
	return 0;
}