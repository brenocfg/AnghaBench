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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_7__ {int crystalfreq; } ;
struct TYPE_8__ {TYPE_3__ pmu; } ;
struct ssb_bus {TYPE_4__ chipco; } ;
struct b43_wldev {TYPE_2__* dev; } ;
struct TYPE_6__ {TYPE_1__* sdev; } ;
struct TYPE_5__ {struct ssb_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2063_PA_SP7 ; 
 int /*<<< orphan*/  B2063_PLL_SP1 ; 
 int /*<<< orphan*/  B2063_RC_CALIB_CTL1 ; 
 int /*<<< orphan*/  B2063_RC_CALIB_CTL2 ; 
 int /*<<< orphan*/  B2063_RC_CALIB_CTL3 ; 
 int /*<<< orphan*/  B2063_RC_CALIB_CTL4 ; 
 int /*<<< orphan*/  B2063_RC_CALIB_CTL5 ; 
 int /*<<< orphan*/  B2063_RC_CALIB_CTL6 ; 
 int /*<<< orphan*/  B2063_RX_BB_SP8 ; 
 int /*<<< orphan*/  B2063_TX_BB_SP3 ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_radio_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void lpphy_rev2plus_rc_calib(struct b43_wldev *dev)
{
	struct ssb_bus *bus = dev->dev->sdev->bus;
	u32 crystal_freq = bus->chipco.pmu.crystalfreq * 1000;
	u8 tmp = b43_radio_read(dev, B2063_RX_BB_SP8) & 0xFF;
	int i;

	b43_radio_write(dev, B2063_RX_BB_SP8, 0x0);
	b43_radio_write(dev, B2063_RC_CALIB_CTL1, 0x7E);
	b43_radio_mask(dev, B2063_PLL_SP1, 0xF7);
	b43_radio_write(dev, B2063_RC_CALIB_CTL1, 0x7C);
	b43_radio_write(dev, B2063_RC_CALIB_CTL2, 0x15);
	b43_radio_write(dev, B2063_RC_CALIB_CTL3, 0x70);
	b43_radio_write(dev, B2063_RC_CALIB_CTL4, 0x52);
	b43_radio_write(dev, B2063_RC_CALIB_CTL5, 0x1);
	b43_radio_write(dev, B2063_RC_CALIB_CTL1, 0x7D);

	for (i = 0; i < 10000; i++) {
		if (b43_radio_read(dev, B2063_RC_CALIB_CTL6) & 0x2)
			break;
		msleep(1);
	}

	if (!(b43_radio_read(dev, B2063_RC_CALIB_CTL6) & 0x2))
		b43_radio_write(dev, B2063_RX_BB_SP8, tmp);

	tmp = b43_radio_read(dev, B2063_TX_BB_SP3) & 0xFF;

	b43_radio_write(dev, B2063_TX_BB_SP3, 0x0);
	b43_radio_write(dev, B2063_RC_CALIB_CTL1, 0x7E);
	b43_radio_write(dev, B2063_RC_CALIB_CTL1, 0x7C);
	b43_radio_write(dev, B2063_RC_CALIB_CTL2, 0x55);
	b43_radio_write(dev, B2063_RC_CALIB_CTL3, 0x76);

	if (crystal_freq == 24000000) {
		b43_radio_write(dev, B2063_RC_CALIB_CTL4, 0xFC);
		b43_radio_write(dev, B2063_RC_CALIB_CTL5, 0x0);
	} else {
		b43_radio_write(dev, B2063_RC_CALIB_CTL4, 0x13);
		b43_radio_write(dev, B2063_RC_CALIB_CTL5, 0x1);
	}

	b43_radio_write(dev, B2063_PA_SP7, 0x7D);

	for (i = 0; i < 10000; i++) {
		if (b43_radio_read(dev, B2063_RC_CALIB_CTL6) & 0x2)
			break;
		msleep(1);
	}

	if (!(b43_radio_read(dev, B2063_RC_CALIB_CTL6) & 0x2))
		b43_radio_write(dev, B2063_TX_BB_SP3, tmp);

	b43_radio_write(dev, B2063_RC_CALIB_CTL1, 0x7E);
}