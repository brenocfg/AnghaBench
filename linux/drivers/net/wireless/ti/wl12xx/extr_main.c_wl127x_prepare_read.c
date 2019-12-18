#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct wl12xx_priv {TYPE_2__* rx_mem_addr; } ;
struct wl1271_acx_mem_map {int /*<<< orphan*/  packet_memory_pool_start; } ;
struct TYPE_3__ {scalar_t__ id; } ;
struct wl1271 {struct wl12xx_priv* priv; struct wl1271_acx_mem_map* target_mem_map; TYPE_1__ chip; } ;
struct TYPE_4__ {scalar_t__ addr; scalar_t__ addr_extra; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_128X_PG20 ; 
 int RX_MEM_BLOCK_MASK ; 
 int /*<<< orphan*/  WL1271_SLV_REG_DATA ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int wlcore_write (struct wl1271*,int /*<<< orphan*/ ,TYPE_2__*,int,int) ; 

__attribute__((used)) static int wl127x_prepare_read(struct wl1271 *wl, u32 rx_desc, u32 len)
{
	int ret;

	if (wl->chip.id != CHIP_ID_128X_PG20) {
		struct wl1271_acx_mem_map *wl_mem_map = wl->target_mem_map;
		struct wl12xx_priv *priv = wl->priv;

		/*
		 * Choose the block we want to read
		 * For aggregated packets, only the first memory block
		 * should be retrieved. The FW takes care of the rest.
		 */
		u32 mem_block = rx_desc & RX_MEM_BLOCK_MASK;

		priv->rx_mem_addr->addr = (mem_block << 8) +
			le32_to_cpu(wl_mem_map->packet_memory_pool_start);

		priv->rx_mem_addr->addr_extra = priv->rx_mem_addr->addr + 4;

		ret = wlcore_write(wl, WL1271_SLV_REG_DATA, priv->rx_mem_addr,
				   sizeof(*priv->rx_mem_addr), false);
		if (ret < 0)
			return ret;
	}

	return 0;
}