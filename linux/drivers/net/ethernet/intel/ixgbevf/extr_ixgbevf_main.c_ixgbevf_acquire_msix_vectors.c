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
struct ixgbevf_adapter {int num_msix_vectors; int /*<<< orphan*/ * msix_entries; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MIN_MSIX_COUNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int pci_enable_msix_range (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int ixgbevf_acquire_msix_vectors(struct ixgbevf_adapter *adapter,
					int vectors)
{
	int vector_threshold;

	/* We'll want at least 2 (vector_threshold):
	 * 1) TxQ[0] + RxQ[0] handler
	 * 2) Other (Link Status Change, etc.)
	 */
	vector_threshold = MIN_MSIX_COUNT;

	/* The more we get, the more we will assign to Tx/Rx Cleanup
	 * for the separate queues...where Rx Cleanup >= Tx Cleanup.
	 * Right now, we simply care about how many we'll get; we'll
	 * set them up later while requesting irq's.
	 */
	vectors = pci_enable_msix_range(adapter->pdev, adapter->msix_entries,
					vector_threshold, vectors);

	if (vectors < 0) {
		dev_err(&adapter->pdev->dev,
			"Unable to allocate MSI-X interrupts\n");
		kfree(adapter->msix_entries);
		adapter->msix_entries = NULL;
		return vectors;
	}

	/* Adjust for only the vectors we'll use, which is minimum
	 * of max_msix_q_vectors + NON_Q_VECTORS, or the number of
	 * vectors we were allocated.
	 */
	adapter->num_msix_vectors = vectors;

	return 0;
}