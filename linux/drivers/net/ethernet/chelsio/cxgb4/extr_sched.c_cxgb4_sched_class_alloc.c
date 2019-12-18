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
typedef  int /*<<< orphan*/  u8 ;
struct sched_class {int dummy; } ;
struct port_info {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  class; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct ch_sched_params {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  can_sched (struct net_device*) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 
 struct sched_class* t4_sched_class_alloc (struct port_info*,struct ch_sched_params*) ; 
 int /*<<< orphan*/  valid_class_id (struct net_device*,int /*<<< orphan*/ ) ; 

struct sched_class *cxgb4_sched_class_alloc(struct net_device *dev,
					    struct ch_sched_params *p)
{
	struct port_info *pi = netdev2pinfo(dev);
	u8 class_id;

	if (!can_sched(dev))
		return NULL;

	class_id = p->u.params.class;
	if (!valid_class_id(dev, class_id))
		return NULL;

	return t4_sched_class_alloc(pi, p);
}