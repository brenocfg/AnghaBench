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
struct drbd_connection {int /*<<< orphan*/  net_conf; } ;

/* Variables and functions */
 int rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline bool has_net_conf(struct drbd_connection *connection)
{
	bool has_net_conf;

	rcu_read_lock();
	has_net_conf = rcu_dereference(connection->net_conf);
	rcu_read_unlock();

	return has_net_conf;
}