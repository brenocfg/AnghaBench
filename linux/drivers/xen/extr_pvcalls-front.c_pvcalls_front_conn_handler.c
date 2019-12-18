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
struct TYPE_2__ {int /*<<< orphan*/  inflight_conn_req; } ;
struct sock_mapping {TYPE_1__ active; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pvcalls_front_conn_handler(int irq, void *sock_map)
{
	struct sock_mapping *map = sock_map;

	if (map == NULL)
		return IRQ_HANDLED;

	wake_up_interruptible(&map->active.inflight_conn_req);

	return IRQ_HANDLED;
}