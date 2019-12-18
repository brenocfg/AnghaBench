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
struct b43_dma {struct b43_dmaring* tx_ring_mcast; struct b43_dmaring* tx_ring_AC_VO; struct b43_dmaring* tx_ring_AC_VI; struct b43_dmaring* tx_ring_AC_BE; struct b43_dmaring* tx_ring_AC_BK; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_dma dma; } ;
struct b43_dmaring {int nr_slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static
struct b43_dmaring *parse_cookie(struct b43_wldev *dev, u16 cookie, int *slot)
{
	struct b43_dma *dma = &dev->dma;
	struct b43_dmaring *ring = NULL;

	switch (cookie & 0xF000) {
	case 0x1000:
		ring = dma->tx_ring_AC_BK;
		break;
	case 0x2000:
		ring = dma->tx_ring_AC_BE;
		break;
	case 0x3000:
		ring = dma->tx_ring_AC_VI;
		break;
	case 0x4000:
		ring = dma->tx_ring_AC_VO;
		break;
	case 0x5000:
		ring = dma->tx_ring_mcast;
		break;
	}
	*slot = (cookie & 0x0FFF);
	if (unlikely(!ring || *slot < 0 || *slot >= ring->nr_slots)) {
		b43dbg(dev->wl, "TX-status contains "
		       "invalid cookie: 0x%04X\n", cookie);
		return NULL;
	}

	return ring;
}