#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct port_info {int nqsets; size_t first_qset; } ;
struct net_device {int dummy; } ;
struct ch_filter_specification {int iq; int /*<<< orphan*/  dirsteer; } ;
struct TYPE_5__ {TYPE_1__* ethrxq; } ;
struct adapter {TYPE_2__ sge; } ;
struct TYPE_6__ {int abs_id; } ;
struct TYPE_4__ {TYPE_3__ rspq; } ;

/* Variables and functions */
 int EINVAL ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int get_filter_steerq(struct net_device *dev,
			     struct ch_filter_specification *fs)
{
	struct adapter *adapter = netdev2adap(dev);
	int iq;

	/* If the user has requested steering matching Ingress Packets
	 * to a specific Queue Set, we need to make sure it's in range
	 * for the port and map that into the Absolute Queue ID of the
	 * Queue Set's Response Queue.
	 */
	if (!fs->dirsteer) {
		if (fs->iq)
			return -EINVAL;
		iq = 0;
	} else {
		struct port_info *pi = netdev_priv(dev);

		/* If the iq id is greater than the number of qsets,
		 * then assume it is an absolute qid.
		 */
		if (fs->iq < pi->nqsets)
			iq = adapter->sge.ethrxq[pi->first_qset +
						 fs->iq].rspq.abs_id;
		else
			iq = fs->iq;
	}

	return iq;
}