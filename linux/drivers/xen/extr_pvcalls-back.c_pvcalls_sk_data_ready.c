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
struct pvcalls_ioworker {int /*<<< orphan*/  register_work; int /*<<< orphan*/  wq; } ;
struct sock_mapping {int /*<<< orphan*/  io; int /*<<< orphan*/  read; struct pvcalls_ioworker ioworker; } ;
struct sock {struct sock_mapping* sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pvcalls_sk_data_ready(struct sock *sock)
{
	struct sock_mapping *map = sock->sk_user_data;
	struct pvcalls_ioworker *iow;

	if (map == NULL)
		return;

	iow = &map->ioworker;
	atomic_inc(&map->read);
	atomic_inc(&map->io);
	queue_work(iow->wq, &iow->register_work);
}