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
struct TYPE_2__ {int /*<<< orphan*/  writen_sync; int /*<<< orphan*/  read32_sync; int /*<<< orphan*/  read16_sync; int /*<<< orphan*/  read8_sync; int /*<<< orphan*/  write32_async; int /*<<< orphan*/  write16_async; int /*<<< orphan*/  write8_async; int /*<<< orphan*/  bb_mutex; struct device* dev; } ;
struct rtl_priv {TYPE_1__ io; } ;
struct ieee80211_hw {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _usb_read16_sync ; 
 int /*<<< orphan*/  _usb_read32_sync ; 
 int /*<<< orphan*/  _usb_read8_sync ; 
 int /*<<< orphan*/  _usb_write16_async ; 
 int /*<<< orphan*/  _usb_write32_async ; 
 int /*<<< orphan*/  _usb_write8_async ; 
 int /*<<< orphan*/  _usb_writen_sync ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl_usb_io_handler_init(struct device *dev,
				     struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->io.dev = dev;
	mutex_init(&rtlpriv->io.bb_mutex);
	rtlpriv->io.write8_async	= _usb_write8_async;
	rtlpriv->io.write16_async	= _usb_write16_async;
	rtlpriv->io.write32_async	= _usb_write32_async;
	rtlpriv->io.read8_sync		= _usb_read8_sync;
	rtlpriv->io.read16_sync		= _usb_read16_sync;
	rtlpriv->io.read32_sync		= _usb_read32_sync;
	rtlpriv->io.writen_sync		= _usb_writen_sync;
}