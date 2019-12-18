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
typedef  int u16 ;
struct b43legacy_dma {struct b43legacy_dmaring* tx_ring5; struct b43legacy_dmaring* tx_ring4; struct b43legacy_dmaring* tx_ring3; struct b43legacy_dmaring* tx_ring2; struct b43legacy_dmaring* tx_ring1; struct b43legacy_dmaring* tx_ring0; } ;
struct b43legacy_wldev {struct b43legacy_dma dma; } ;
struct b43legacy_dmaring {int nr_slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 

__attribute__((used)) static
struct b43legacy_dmaring *parse_cookie(struct b43legacy_wldev *dev,
				      u16 cookie, int *slot)
{
	struct b43legacy_dma *dma = &dev->dma;
	struct b43legacy_dmaring *ring = NULL;

	switch (cookie & 0xF000) {
	case 0xA000:
		ring = dma->tx_ring0;
		break;
	case 0xB000:
		ring = dma->tx_ring1;
		break;
	case 0xC000:
		ring = dma->tx_ring2;
		break;
	case 0xD000:
		ring = dma->tx_ring3;
		break;
	case 0xE000:
		ring = dma->tx_ring4;
		break;
	case 0xF000:
		ring = dma->tx_ring5;
		break;
	default:
		B43legacy_WARN_ON(1);
	}
	*slot = (cookie & 0x0FFF);
	B43legacy_WARN_ON(!(ring && *slot >= 0 && *slot < ring->nr_slots));

	return ring;
}