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
struct TYPE_2__ {int multi_clks; } ;
struct usbhs_priv {TYPE_1__ dparam; } ;

/* Variables and functions */

__attribute__((used)) static bool usbhsc_is_multi_clks(struct usbhs_priv *priv)
{
	return priv->dparam.multi_clks;
}