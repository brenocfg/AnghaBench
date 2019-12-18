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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct device* dev; } ;
struct rtl_priv {TYPE_1__ io; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _usb_write_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_usb_device (struct device*) ; 

__attribute__((used)) static void _usb_write8_async(struct rtl_priv *rtlpriv, u32 addr, u8 val)
{
	struct device *dev = rtlpriv->io.dev;

	_usb_write_async(to_usb_device(dev), addr, val, 1);
}