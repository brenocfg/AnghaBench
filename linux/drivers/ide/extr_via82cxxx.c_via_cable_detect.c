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
typedef  int u32 ;
struct via82cxxx_dev {int via_80w; TYPE_1__* via_config; } ;
struct TYPE_2__ {int udma_mask; } ;

/* Variables and functions */
#define  ATA_UDMA4 130 
#define  ATA_UDMA5 129 
#define  ATA_UDMA6 128 

__attribute__((used)) static void via_cable_detect(struct via82cxxx_dev *vdev, u32 u)
{
	int i;

	switch (vdev->via_config->udma_mask) {
		case ATA_UDMA4:
			for (i = 24; i >= 0; i -= 8)
				if (((u >> (i & 16)) & 8) &&
				    ((u >> i) & 0x20) &&
				     (((u >> i) & 7) < 2)) {
					/*
					 * 2x PCI clock and
					 * UDMA w/ < 3T/cycle
					 */
					vdev->via_80w |= (1 << (1 - (i >> 4)));
				}
			break;

		case ATA_UDMA5:
			for (i = 24; i >= 0; i -= 8)
				if (((u >> i) & 0x10) ||
				    (((u >> i) & 0x20) &&
				     (((u >> i) & 7) < 4))) {
					/* BIOS 80-wire bit or
					 * UDMA w/ < 60ns/cycle
					 */
					vdev->via_80w |= (1 << (1 - (i >> 4)));
				}
			break;

		case ATA_UDMA6:
			for (i = 24; i >= 0; i -= 8)
				if (((u >> i) & 0x10) ||
				    (((u >> i) & 0x20) &&
				     (((u >> i) & 7) < 6))) {
					/* BIOS 80-wire bit or
					 * UDMA w/ < 60ns/cycle
					 */
					vdev->via_80w |= (1 << (1 - (i >> 4)));
				}
			break;
	}
}