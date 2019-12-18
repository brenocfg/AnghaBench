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
struct TYPE_2__ {int /*<<< orphan*/  read32_sync; int /*<<< orphan*/  read16_sync; int /*<<< orphan*/  read8_sync; int /*<<< orphan*/  write32_async; int /*<<< orphan*/  write16_async; int /*<<< orphan*/  write8_async; struct device* dev; } ;
struct rtl_priv {TYPE_1__ io; } ;
struct ieee80211_hw {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read16_sync ; 
 int /*<<< orphan*/  pci_read32_sync ; 
 int /*<<< orphan*/  pci_read8_sync ; 
 int /*<<< orphan*/  pci_write16_async ; 
 int /*<<< orphan*/  pci_write32_async ; 
 int /*<<< orphan*/  pci_write8_async ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl_pci_io_handler_init(struct device *dev,
				     struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->io.dev = dev;

	rtlpriv->io.write8_async = pci_write8_async;
	rtlpriv->io.write16_async = pci_write16_async;
	rtlpriv->io.write32_async = pci_write32_async;

	rtlpriv->io.read8_sync = pci_read8_sync;
	rtlpriv->io.read16_sync = pci_read16_sync;
	rtlpriv->io.read32_sync = pci_read32_sync;
}