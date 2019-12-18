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
struct i801_priv {int features; int /*<<< orphan*/  original_slvcmd; } ;

/* Variables and functions */
 int FEATURE_HOST_NOTIFY ; 
 int /*<<< orphan*/  SMBSLVCMD (struct i801_priv*) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i801_disable_host_notify(struct i801_priv *priv)
{
	if (!(priv->features & FEATURE_HOST_NOTIFY))
		return;

	outb_p(priv->original_slvcmd, SMBSLVCMD(priv));
}