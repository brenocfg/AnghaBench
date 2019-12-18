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
struct i801_priv {int /*<<< orphan*/  adapter; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SMBNTFDADD (struct i801_priv*) ; 
 int /*<<< orphan*/  SMBSLVSTS (struct i801_priv*) ; 
 int /*<<< orphan*/  SMBSLVSTS_HST_NTFY_STS ; 
 int /*<<< orphan*/  i2c_handle_smbus_host_notify (int /*<<< orphan*/ *,unsigned short) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t i801_host_notify_isr(struct i801_priv *priv)
{
	unsigned short addr;

	addr = inb_p(SMBNTFDADD(priv)) >> 1;

	/*
	 * With the tested platforms, reading SMBNTFDDAT (22 + (p)->smba)
	 * always returns 0. Our current implementation doesn't provide
	 * data, so we just ignore it.
	 */
	i2c_handle_smbus_host_notify(&priv->adapter, addr);

	/* clear Host Notify bit and return */
	outb_p(SMBSLVSTS_HST_NTFY_STS, SMBSLVSTS(priv));
	return IRQ_HANDLED;
}