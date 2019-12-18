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
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt76u_free_rx (struct mt76_dev*) ; 
 int /*<<< orphan*/  mt76u_free_tx (struct mt76_dev*) ; 
 int /*<<< orphan*/  mt76u_stop_rx (struct mt76_dev*) ; 
 int /*<<< orphan*/  mt76u_stop_tx (struct mt76_dev*) ; 

void mt76u_queues_deinit(struct mt76_dev *dev)
{
	mt76u_stop_rx(dev);
	mt76u_stop_tx(dev);

	mt76u_free_rx(dev);
	mt76u_free_tx(dev);
}