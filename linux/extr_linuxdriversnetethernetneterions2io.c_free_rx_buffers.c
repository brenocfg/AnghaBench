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
struct mac_info {struct ring_info* rings; } ;
struct config_param {int rx_ring_num; } ;
struct s2io_nic {struct mac_info mac_control; struct config_param config; struct net_device* dev; } ;
struct TYPE_4__ {scalar_t__ offset; scalar_t__ block_index; } ;
struct TYPE_3__ {scalar_t__ offset; scalar_t__ block_index; } ;
struct ring_info {scalar_t__ rx_bufs_left; TYPE_2__ rx_curr_get_info; TYPE_1__ rx_curr_put_info; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  INIT_DBG ; 
 int /*<<< orphan*/  free_rxd_blk (struct s2io_nic*,int,int) ; 
 int* rx_ring_sz ; 

__attribute__((used)) static void free_rx_buffers(struct s2io_nic *sp)
{
	struct net_device *dev = sp->dev;
	int i, blk = 0, buf_cnt = 0;
	struct config_param *config = &sp->config;
	struct mac_info *mac_control = &sp->mac_control;

	for (i = 0; i < config->rx_ring_num; i++) {
		struct ring_info *ring = &mac_control->rings[i];

		for (blk = 0; blk < rx_ring_sz[i]; blk++)
			free_rxd_blk(sp, i, blk);

		ring->rx_curr_put_info.block_index = 0;
		ring->rx_curr_get_info.block_index = 0;
		ring->rx_curr_put_info.offset = 0;
		ring->rx_curr_get_info.offset = 0;
		ring->rx_bufs_left = 0;
		DBG_PRINT(INIT_DBG, "%s: Freed 0x%x Rx Buffers on ring%d\n",
			  dev->name, buf_cnt, i);
	}
}