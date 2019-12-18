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
struct sock_mapping {int /*<<< orphan*/  irq; int /*<<< orphan*/  read; } ;
struct sock {struct sock_mapping* sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvcalls_sk_state_change(struct sock *sock)
{
	struct sock_mapping *map = sock->sk_user_data;

	if (map == NULL)
		return;

	atomic_inc(&map->read);
	notify_remote_via_irq(map->irq);
}