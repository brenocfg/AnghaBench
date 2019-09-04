#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nic {int /*<<< orphan*/  watchdog; int /*<<< orphan*/  napi; TYPE_2__* netdev; TYPE_1__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int e100_alloc_cbs (struct nic*) ; 
 int /*<<< orphan*/  e100_clean_cbs (struct nic*) ; 
 int /*<<< orphan*/  e100_enable_irq (struct nic*) ; 
 int e100_hw_init (struct nic*) ; 
 int /*<<< orphan*/  e100_intr ; 
 int e100_rx_alloc_list (struct nic*) ; 
 int /*<<< orphan*/  e100_rx_clean_list (struct nic*) ; 
 int /*<<< orphan*/  e100_set_multicast_list (TYPE_2__*) ; 
 int /*<<< orphan*/  e100_start_receiver (struct nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_2__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int e100_up(struct nic *nic)
{
	int err;

	if ((err = e100_rx_alloc_list(nic)))
		return err;
	if ((err = e100_alloc_cbs(nic)))
		goto err_rx_clean_list;
	if ((err = e100_hw_init(nic)))
		goto err_clean_cbs;
	e100_set_multicast_list(nic->netdev);
	e100_start_receiver(nic, NULL);
	mod_timer(&nic->watchdog, jiffies);
	if ((err = request_irq(nic->pdev->irq, e100_intr, IRQF_SHARED,
		nic->netdev->name, nic->netdev)))
		goto err_no_irq;
	netif_wake_queue(nic->netdev);
	napi_enable(&nic->napi);
	/* enable ints _after_ enabling poll, preventing a race between
	 * disable ints+schedule */
	e100_enable_irq(nic);
	return 0;

err_no_irq:
	del_timer_sync(&nic->watchdog);
err_clean_cbs:
	e100_clean_cbs(nic);
err_rx_clean_list:
	e100_rx_clean_list(nic);
	return err;
}