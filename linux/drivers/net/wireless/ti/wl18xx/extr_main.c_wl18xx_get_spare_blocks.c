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
struct wl18xx_priv {scalar_t__ extra_spare_key_count; } ;
struct wl1271 {struct wl18xx_priv* priv; } ;

/* Variables and functions */
 int WL18XX_TX_HW_BLOCK_SPARE ; 
 int WL18XX_TX_HW_EXTRA_BLOCK_SPARE ; 

__attribute__((used)) static int wl18xx_get_spare_blocks(struct wl1271 *wl, bool is_gem)
{
	struct wl18xx_priv *priv = wl->priv;

	/* If we have keys requiring extra spare, indulge them */
	if (priv->extra_spare_key_count)
		return WL18XX_TX_HW_EXTRA_BLOCK_SPARE;

	return WL18XX_TX_HW_BLOCK_SPARE;
}