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
struct sdio_func {int dummy; } ;
struct ks_wlan_private {struct ks_sdio_card* if_hw; } ;
struct ks_sdio_card {struct sdio_func* func; } ;

/* Variables and functions */

__attribute__((used)) static struct sdio_func *ks7010_to_func(struct ks_wlan_private *priv)
{
	struct ks_sdio_card *ks_sdio = priv->if_hw;

	return ks_sdio->func;
}