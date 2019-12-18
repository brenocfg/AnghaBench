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
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2063_COMM8 ; 
 int /*<<< orphan*/  B2063_LOGEN_SP5 ; 
 int /*<<< orphan*/  B2063_PA_SP2 ; 
 int /*<<< orphan*/  B2063_PA_SP3 ; 
 int /*<<< orphan*/  B2063_PA_SP4 ; 
 int /*<<< orphan*/  B2063_PA_SP7 ; 
 int /*<<< orphan*/  B2063_REG_SP1 ; 
 int /*<<< orphan*/  B2063_RX_BB_CTL2 ; 
 int /*<<< orphan*/  B2063_TX_RF_SP6 ; 
 int /*<<< orphan*/  B2063_TX_RF_SP9 ; 
 int /*<<< orphan*/  b2063_upload_init_table (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpphy_2063_init(struct b43_wldev *dev)
{
	b2063_upload_init_table(dev);
	b43_radio_write(dev, B2063_LOGEN_SP5, 0);
	b43_radio_set(dev, B2063_COMM8, 0x38);
	b43_radio_write(dev, B2063_REG_SP1, 0x56);
	b43_radio_mask(dev, B2063_RX_BB_CTL2, ~0x2);
	b43_radio_write(dev, B2063_PA_SP7, 0);
	b43_radio_write(dev, B2063_TX_RF_SP6, 0x20);
	b43_radio_write(dev, B2063_TX_RF_SP9, 0x40);
	if (dev->phy.rev == 2) {
		b43_radio_write(dev, B2063_PA_SP3, 0xa0);
		b43_radio_write(dev, B2063_PA_SP4, 0xa0);
		b43_radio_write(dev, B2063_PA_SP2, 0x18);
	} else {
		b43_radio_write(dev, B2063_PA_SP3, 0x20);
		b43_radio_write(dev, B2063_PA_SP2, 0x20);
	}
}