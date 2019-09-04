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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {char** names; int /*<<< orphan*/  irqs; struct msix_entry* entries; } ;
struct TYPE_3__ {struct nitrox_device* slc; } ;
struct nitrox_device {int nr_queues; int idx; TYPE_2__ msix; TYPE_1__ bh; struct pci_dev* pdev; } ;
struct msix_entry {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_MSIX_VECTOR_NAME ; 
 int NR_RING_VECTORS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_cpu_mask (int) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nps_core_int_isr ; 
 int /*<<< orphan*/  nps_pkt_slc_isr ; 
 int num_online_cpus () ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct nitrox_device*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int nitrox_request_irqs(struct nitrox_device *ndev)
{
	struct pci_dev *pdev = ndev->pdev;
	struct msix_entry *msix_ent = ndev->msix.entries;
	int nr_ring_vectors, i = 0, ring, cpu, ret;
	char *name;

	/*
	 * PF MSI-X vectors
	 *
	 * Entry 0: NPS PKT ring 0
	 * Entry 1: AQMQ ring 0
	 * Entry 2: ZQM ring 0
	 * Entry 3: NPS PKT ring 1
	 * ....
	 * Entry 192: NPS_CORE_INT_ACTIVE
	 */
	nr_ring_vectors = ndev->nr_queues * NR_RING_VECTORS;

	/* request irq for pkt ring/ports only */
	while (i < nr_ring_vectors) {
		name = *(ndev->msix.names + i);
		ring = (i / NR_RING_VECTORS);
		snprintf(name, MAX_MSIX_VECTOR_NAME, "n5(%d)-slc-ring%d",
			 ndev->idx, ring);

		ret = request_irq(msix_ent[i].vector, nps_pkt_slc_isr, 0,
				  name, &ndev->bh.slc[ring]);
		if (ret) {
			dev_err(&pdev->dev, "failed to get irq %d for %s\n",
				msix_ent[i].vector, name);
			return ret;
		}
		cpu = ring % num_online_cpus();
		irq_set_affinity_hint(msix_ent[i].vector, get_cpu_mask(cpu));

		set_bit(i, ndev->msix.irqs);
		i += NR_RING_VECTORS;
	}

	/* Request IRQ for NPS_CORE_INT_ACTIVE */
	name = *(ndev->msix.names + i);
	snprintf(name, MAX_MSIX_VECTOR_NAME, "n5(%d)-nps-core-int", ndev->idx);
	ret = request_irq(msix_ent[i].vector, nps_core_int_isr, 0, name, ndev);
	if (ret) {
		dev_err(&pdev->dev, "failed to get irq %d for %s\n",
			msix_ent[i].vector, name);
		return ret;
	}
	set_bit(i, ndev->msix.irqs);

	return 0;
}