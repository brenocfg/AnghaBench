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
typedef  int /*<<< orphan*/  u_long ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  save_cnt; } ;
struct de4x5_private {TYPE_1__ cache; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DE4X5_RESTORE_STATE ; 
 int /*<<< orphan*/  DE4X5_SAVE_STATE ; 
 int /*<<< orphan*/  START_DE4X5 ; 
 int /*<<< orphan*/  STOP_DE4X5 ; 
 int /*<<< orphan*/  de4x5_cache_state (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  de4x5_free_tx_buffs (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_sw_reset (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_tx (struct net_device*) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
de4x5_save_skbs(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    s32 omr;

    if (!lp->cache.save_cnt) {
	STOP_DE4X5;
	de4x5_tx(dev);                          /* Flush any sent skb's */
	de4x5_free_tx_buffs(dev);
	de4x5_cache_state(dev, DE4X5_SAVE_STATE);
	de4x5_sw_reset(dev);
	de4x5_cache_state(dev, DE4X5_RESTORE_STATE);
	lp->cache.save_cnt++;
	START_DE4X5;
    }
}