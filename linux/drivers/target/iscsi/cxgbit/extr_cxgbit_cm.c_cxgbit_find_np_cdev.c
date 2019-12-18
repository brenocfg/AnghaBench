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
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {struct sockaddr_storage local_addr; } ;
struct cxgbit_np {TYPE_2__ com; } ;
struct cxgbit_device {int dummy; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 struct cxgbit_device* cxgbit_find_device (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* cxgbit_ipv4_netdev (int /*<<< orphan*/ ) ; 
 struct net_device* cxgbit_ipv6_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct cxgbit_device *cxgbit_find_np_cdev(struct cxgbit_np *cnp)
{
	struct sockaddr_storage *sockaddr = &cnp->com.local_addr;
	int ss_family = sockaddr->ss_family;
	struct net_device *ndev = NULL;
	struct cxgbit_device *cdev = NULL;

	rcu_read_lock();
	if (ss_family == AF_INET) {
		struct sockaddr_in *sin;

		sin = (struct sockaddr_in *)sockaddr;
		ndev = cxgbit_ipv4_netdev(sin->sin_addr.s_addr);
	} else if (ss_family == AF_INET6) {
		struct sockaddr_in6 *sin6;

		sin6 = (struct sockaddr_in6 *)sockaddr;
		ndev = cxgbit_ipv6_netdev(&sin6->sin6_addr);
	}
	if (!ndev)
		goto out;

	cdev = cxgbit_find_device(ndev, NULL);
out:
	rcu_read_unlock();
	return cdev;
}