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
typedef  int /*<<< orphan*/  u32 ;
struct b43legacy_phy {int /*<<< orphan*/ * lo_control; int /*<<< orphan*/ * tssi2dbm; scalar_t__ dyn_tssi_tbl; } ;
struct b43legacy_wldev {TYPE_1__* dev; TYPE_2__* wl; struct b43legacy_phy phy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * current_beacon; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MACCTL_PSM_JMP0 ; 
 int /*<<< orphan*/  B43legacy_MACCTL_PSM_RUN ; 
 int /*<<< orphan*/  B43legacy_MMIO_MACCTL ; 
 scalar_t__ B43legacy_STAT_INITIALIZED ; 
 int /*<<< orphan*/  B43legacy_STAT_UNINIT ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  b43legacy_chip_exit (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_dma_free (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_leds_exit (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_pio_free (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_radio_turn_off (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_rng_exit (TYPE_2__*) ; 
 int /*<<< orphan*/  b43legacy_set_status (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_switch_analog (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_bus_may_powerdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_device_disable (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43legacy_wireless_core_exit(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	u32 macctl;

	B43legacy_WARN_ON(b43legacy_status(dev) > B43legacy_STAT_INITIALIZED);
	if (b43legacy_status(dev) != B43legacy_STAT_INITIALIZED)
		return;
	b43legacy_set_status(dev, B43legacy_STAT_UNINIT);

	/* Stop the microcode PSM. */
	macctl = b43legacy_read32(dev, B43legacy_MMIO_MACCTL);
	macctl &= ~B43legacy_MACCTL_PSM_RUN;
	macctl |= B43legacy_MACCTL_PSM_JMP0;
	b43legacy_write32(dev, B43legacy_MMIO_MACCTL, macctl);

	b43legacy_leds_exit(dev);
	b43legacy_rng_exit(dev->wl);
	b43legacy_pio_free(dev);
	b43legacy_dma_free(dev);
	b43legacy_chip_exit(dev);
	b43legacy_radio_turn_off(dev, 1);
	b43legacy_switch_analog(dev, 0);
	if (phy->dyn_tssi_tbl)
		kfree(phy->tssi2dbm);
	kfree(phy->lo_control);
	phy->lo_control = NULL;
	if (dev->wl->current_beacon) {
		dev_kfree_skb_any(dev->wl->current_beacon);
		dev->wl->current_beacon = NULL;
	}

	ssb_device_disable(dev->dev, 0);
	ssb_bus_may_powerdown(dev->dev->bus);
}