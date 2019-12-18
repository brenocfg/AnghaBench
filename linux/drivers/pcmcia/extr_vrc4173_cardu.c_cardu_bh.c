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
struct TYPE_2__ {int /*<<< orphan*/  info; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  event_lock; scalar_t__ events; } ;
typedef  TYPE_1__ vrc4173_socket_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cardu_bh(void *data)
{
	vrc4173_socket_t *socket = (vrc4173_socket_t *)data;
	uint16_t events;

	spin_lock_irq(&socket->event_lock);
	events = socket->events;
	socket->events = 0;
	spin_unlock_irq(&socket->event_lock);

	if (socket->handler)
		socket->handler(socket->info, events);
}