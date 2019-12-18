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
typedef  scalar_t__ u8 ;
struct port_info {int dummy; } ;
struct net_device {int dummy; } ;
struct ch_sched_queue {scalar_t__ class; } ;
typedef  enum sched_bind_type { ____Placeholder_sched_bind_type } sched_bind_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 scalar_t__ SCHED_CLS_NONE ; 
#define  SCHED_QUEUE 128 
 int /*<<< orphan*/  can_sched (struct net_device*) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 
 int t4_sched_class_bind_unbind_op (struct port_info*,void*,int,int) ; 
 int /*<<< orphan*/  valid_class_id (struct net_device*,scalar_t__) ; 

int cxgb4_sched_class_bind(struct net_device *dev, void *arg,
			   enum sched_bind_type type)
{
	struct port_info *pi = netdev2pinfo(dev);
	u8 class_id;

	if (!can_sched(dev))
		return -ENOTSUPP;

	if (!arg)
		return -EINVAL;

	switch (type) {
	case SCHED_QUEUE: {
		struct ch_sched_queue *qe = (struct ch_sched_queue *)arg;

		class_id = qe->class;
		break;
	}
	default:
		return -ENOTSUPP;
	}

	if (!valid_class_id(dev, class_id))
		return -EINVAL;

	if (class_id == SCHED_CLS_NONE)
		return -ENOTSUPP;

	return t4_sched_class_bind_unbind_op(pi, arg, type, true);

}