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
struct ag71xx {int /*<<< orphan*/  oom_timer; int /*<<< orphan*/  napi; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ag71xx_dma_reset (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_hw_stop (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_rings_cleanup (struct ag71xx*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ag71xx_hw_disable(struct ag71xx *ag)
{
	netif_stop_queue(ag->ndev);

	ag71xx_hw_stop(ag);
	ag71xx_dma_reset(ag);

	napi_disable(&ag->napi);
	del_timer_sync(&ag->oom_timer);

	ag71xx_rings_cleanup(ag);
}