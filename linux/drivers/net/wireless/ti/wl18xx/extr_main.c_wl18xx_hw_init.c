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
struct wl18xx_priv {scalar_t__ extra_spare_key_count; scalar_t__ last_fw_rls_idx; } ;
struct wl1271 {struct wl18xx_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL18XX_TX_HW_BLOCK_SPARE ; 
 scalar_t__ checksum_param ; 
 int wl18xx_acx_dynamic_fw_traces (struct wl1271*) ; 
 int wl18xx_acx_set_checksum_state (struct wl1271*) ; 
 int wl18xx_set_host_cfg_bitmap (struct wl1271*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl18xx_hw_init(struct wl1271 *wl)
{
	int ret;
	struct wl18xx_priv *priv = wl->priv;

	/* (re)init private structures. Relevant on recovery as well. */
	priv->last_fw_rls_idx = 0;
	priv->extra_spare_key_count = 0;

	/* set the default amount of spare blocks in the bitmap */
	ret = wl18xx_set_host_cfg_bitmap(wl, WL18XX_TX_HW_BLOCK_SPARE);
	if (ret < 0)
		return ret;

	/* set the dynamic fw traces bitmap */
	ret = wl18xx_acx_dynamic_fw_traces(wl);
	if (ret < 0)
		return ret;

	if (checksum_param) {
		ret = wl18xx_acx_set_checksum_state(wl);
		if (ret != 0)
			return ret;
	}

	return ret;
}