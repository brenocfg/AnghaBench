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
struct i801_priv {int features; int original_slvcmd; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int FEATURE_HOST_NOTIFY ; 
 int /*<<< orphan*/  SMBSLVCMD (struct i801_priv*) ; 
 int SMBSLVCMD_HST_NTFY_INTREN ; 
 int /*<<< orphan*/  SMBSLVSTS (struct i801_priv*) ; 
 int SMBSLVSTS_HST_NTFY_STS ; 
 struct i801_priv* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i801_enable_host_notify(struct i2c_adapter *adapter)
{
	struct i801_priv *priv = i2c_get_adapdata(adapter);

	if (!(priv->features & FEATURE_HOST_NOTIFY))
		return;

	if (!(SMBSLVCMD_HST_NTFY_INTREN & priv->original_slvcmd))
		outb_p(SMBSLVCMD_HST_NTFY_INTREN | priv->original_slvcmd,
		       SMBSLVCMD(priv));

	/* clear Host Notify bit to allow a new notification */
	outb_p(SMBSLVSTS_HST_NTFY_STS, SMBSLVSTS(priv));
}