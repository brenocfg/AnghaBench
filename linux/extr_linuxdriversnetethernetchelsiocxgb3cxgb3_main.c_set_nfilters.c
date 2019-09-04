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
struct port_info {struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int nservers; unsigned int nfilters; } ;
struct TYPE_4__ {scalar_t__ rev; TYPE_1__ mc5; } ;
struct adapter {int flags; TYPE_2__ params; int /*<<< orphan*/  mc5; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int FULL_INIT_DONE ; 
 int MC5_MIN_TIDS ; 
 scalar_t__ is_offload (struct adapter*) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t3_mc5_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t set_nfilters(struct net_device *dev, unsigned int val)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adap = pi->adapter;
	int min_tids = is_offload(adap) ? MC5_MIN_TIDS : 0;

	if (adap->flags & FULL_INIT_DONE)
		return -EBUSY;
	if (val && adap->params.rev == 0)
		return -EINVAL;
	if (val > t3_mc5_size(&adap->mc5) - adap->params.mc5.nservers -
	    min_tids)
		return -EINVAL;
	adap->params.mc5.nfilters = val;
	return 0;
}