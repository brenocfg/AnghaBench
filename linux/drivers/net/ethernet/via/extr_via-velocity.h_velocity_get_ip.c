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
struct velocity_info {int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  netdev; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_address; } ;
struct in_device {int /*<<< orphan*/  ifa_list; } ;

/* Variables and functions */
 int ENOENT ; 
 struct in_device* __in_dev_get_rcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct in_ifaddr* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline int velocity_get_ip(struct velocity_info *vptr)
{
	struct in_device *in_dev;
	struct in_ifaddr *ifa;
	int res = -ENOENT;

	rcu_read_lock();
	in_dev = __in_dev_get_rcu(vptr->netdev);
	if (in_dev != NULL) {
		ifa = rcu_dereference(in_dev->ifa_list);
		if (ifa != NULL) {
			memcpy(vptr->ip_addr, &ifa->ifa_address, 4);
			res = 0;
		}
	}
	rcu_read_unlock();
	return res;
}