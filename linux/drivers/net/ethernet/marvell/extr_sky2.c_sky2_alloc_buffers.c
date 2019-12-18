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
struct tx_ring_info {int dummy; } ;
struct sky2_tx_le {int dummy; } ;
struct sky2_port {int tx_ring_size; int rx_pending; void* rx_ring; int /*<<< orphan*/  rx_le; int /*<<< orphan*/  rx_le_map; void* tx_ring; int /*<<< orphan*/  tx_le; int /*<<< orphan*/  tx_le_map; struct sky2_hw* hw; } ;
struct sky2_hw {int /*<<< orphan*/  pdev; } ;
struct rx_ring_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RX_LE_BYTES ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_zalloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sky2_alloc_rx_skbs (struct sky2_port*) ; 

__attribute__((used)) static int sky2_alloc_buffers(struct sky2_port *sky2)
{
	struct sky2_hw *hw = sky2->hw;

	/* must be power of 2 */
	sky2->tx_le = pci_alloc_consistent(hw->pdev,
					   sky2->tx_ring_size *
					   sizeof(struct sky2_tx_le),
					   &sky2->tx_le_map);
	if (!sky2->tx_le)
		goto nomem;

	sky2->tx_ring = kcalloc(sky2->tx_ring_size, sizeof(struct tx_ring_info),
				GFP_KERNEL);
	if (!sky2->tx_ring)
		goto nomem;

	sky2->rx_le = pci_zalloc_consistent(hw->pdev, RX_LE_BYTES,
					    &sky2->rx_le_map);
	if (!sky2->rx_le)
		goto nomem;

	sky2->rx_ring = kcalloc(sky2->rx_pending, sizeof(struct rx_ring_info),
				GFP_KERNEL);
	if (!sky2->rx_ring)
		goto nomem;

	return sky2_alloc_rx_skbs(sky2);
nomem:
	return -ENOMEM;
}