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
struct pvcalls_ioworker {int /*<<< orphan*/  register_work; int /*<<< orphan*/  wq; } ;
struct sock_mapping {int /*<<< orphan*/  io; int /*<<< orphan*/  write; struct pvcalls_ioworker ioworker; TYPE_2__* sock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {TYPE_1__* sk; } ;
struct TYPE_3__ {struct sock_mapping* sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pvcalls_back_conn_event(int irq, void *sock_map)
{
	struct sock_mapping *map = sock_map;
	struct pvcalls_ioworker *iow;

	if (map == NULL || map->sock == NULL || map->sock->sk == NULL ||
		map->sock->sk->sk_user_data != map)
		return IRQ_HANDLED;

	iow = &map->ioworker;

	atomic_inc(&map->write);
	atomic_inc(&map->io);
	queue_work(iow->wq, &iow->register_work);

	return IRQ_HANDLED;
}