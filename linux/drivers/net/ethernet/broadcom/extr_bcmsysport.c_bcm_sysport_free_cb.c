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
struct bcm_sysport_cb {int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_consume_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct bcm_sysport_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sysport_free_cb(struct bcm_sysport_cb *cb)
{
	dev_consume_skb_any(cb->skb);
	cb->skb = NULL;
	dma_unmap_addr_set(cb, dma_addr, 0);
}