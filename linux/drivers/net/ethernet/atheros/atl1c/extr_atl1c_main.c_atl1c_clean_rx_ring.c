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
struct pci_dev {int dummy; } ;
struct atl1c_rrd_ring {scalar_t__ next_to_clean; scalar_t__ next_to_use; } ;
struct atl1c_rfd_ring {int count; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/  size; int /*<<< orphan*/  desc; struct atl1c_buffer* buffer_info; } ;
struct atl1c_buffer {int dummy; } ;
struct atl1c_adapter {struct pci_dev* pdev; struct atl1c_rrd_ring rrd_ring; struct atl1c_rfd_ring rfd_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  atl1c_clean_buffer (struct pci_dev*,struct atl1c_buffer*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl1c_clean_rx_ring(struct atl1c_adapter *adapter)
{
	struct atl1c_rfd_ring *rfd_ring = &adapter->rfd_ring;
	struct atl1c_rrd_ring *rrd_ring = &adapter->rrd_ring;
	struct atl1c_buffer *buffer_info;
	struct pci_dev *pdev = adapter->pdev;
	int j;

	for (j = 0; j < rfd_ring->count; j++) {
		buffer_info = &rfd_ring->buffer_info[j];
		atl1c_clean_buffer(pdev, buffer_info);
	}
	/* zero out the descriptor ring */
	memset(rfd_ring->desc, 0, rfd_ring->size);
	rfd_ring->next_to_clean = 0;
	rfd_ring->next_to_use = 0;
	rrd_ring->next_to_use = 0;
	rrd_ring->next_to_clean = 0;
}