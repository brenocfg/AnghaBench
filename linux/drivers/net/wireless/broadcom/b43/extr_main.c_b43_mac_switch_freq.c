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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_4__ {scalar_t__ type; } ;
struct b43_wldev {TYPE_2__ phy; TYPE_1__* dev; } ;
struct TYPE_3__ {scalar_t__ chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_TSF_CLK_FRAC_HIGH ; 
 int /*<<< orphan*/  B43_MMIO_TSF_CLK_FRAC_LOW ; 
 scalar_t__ B43_PHYTYPE_LCN ; 
 scalar_t__ BCMA_CHIP_ID_BCM43131 ; 
 scalar_t__ BCMA_CHIP_ID_BCM43217 ; 
 scalar_t__ BCMA_CHIP_ID_BCM43222 ; 
 scalar_t__ BCMA_CHIP_ID_BCM43224 ; 
 scalar_t__ BCMA_CHIP_ID_BCM43225 ; 
 scalar_t__ BCMA_CHIP_ID_BCM43227 ; 
 scalar_t__ BCMA_CHIP_ID_BCM43228 ; 
 scalar_t__ BCMA_CHIP_ID_BCM4331 ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

void b43_mac_switch_freq(struct b43_wldev *dev, u8 spurmode)
{
	u16 chip_id = dev->dev->chip_id;

	if (chip_id == BCMA_CHIP_ID_BCM4331) {
		switch (spurmode) {
		case 2: /* 168 Mhz: 2^26/168 = 0x61862 */
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x1862);
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x6);
			break;
		case 1: /* 164 Mhz: 2^26/164 = 0x63e70 */
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x3e70);
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x6);
			break;
		default: /* 160 Mhz: 2^26/160 = 0x66666 */
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x6666);
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x6);
			break;
		}
	} else if (chip_id == BCMA_CHIP_ID_BCM43131 ||
	    chip_id == BCMA_CHIP_ID_BCM43217 ||
	    chip_id == BCMA_CHIP_ID_BCM43222 ||
	    chip_id == BCMA_CHIP_ID_BCM43224 ||
	    chip_id == BCMA_CHIP_ID_BCM43225 ||
	    chip_id == BCMA_CHIP_ID_BCM43227 ||
	    chip_id == BCMA_CHIP_ID_BCM43228) {
		switch (spurmode) {
		case 2: /* 126 Mhz */
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x2082);
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x8);
			break;
		case 1: /* 123 Mhz */
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x5341);
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x8);
			break;
		default: /* 120 Mhz */
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x8889);
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x8);
			break;
		}
	} else if (dev->phy.type == B43_PHYTYPE_LCN) {
		switch (spurmode) {
		case 1: /* 82 Mhz */
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0x7CE0);
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0xC);
			break;
		default: /* 80 Mhz */
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, 0xCCCD);
			b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0xC);
			break;
		}
	}
}