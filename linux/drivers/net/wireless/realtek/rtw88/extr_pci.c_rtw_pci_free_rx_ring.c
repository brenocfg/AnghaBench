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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int desc_size; int len; int /*<<< orphan*/  dma; int /*<<< orphan*/ * head; } ;
struct rtw_pci_rx_ring {TYPE_1__ r; } ;
struct rtw_dev {int /*<<< orphan*/  dev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_pci_free_rx_ring_skbs (struct rtw_dev*,struct rtw_pci_rx_ring*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_pci_free_rx_ring(struct rtw_dev *rtwdev,
				 struct rtw_pci_rx_ring *rx_ring)
{
	struct pci_dev *pdev = to_pci_dev(rtwdev->dev);
	u8 *head = rx_ring->r.head;
	int ring_sz = rx_ring->r.desc_size * rx_ring->r.len;

	rtw_pci_free_rx_ring_skbs(rtwdev, rx_ring);

	pci_free_consistent(pdev, ring_sz, head, rx_ring->r.dma);
}