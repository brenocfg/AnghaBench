#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {struct net_device* dev; TYPE_1__* local; } ;
typedef  TYPE_2__ isdn_net_dev ;
struct TYPE_4__ {scalar_t__ isdn_device; struct net_device* slave; } ;

/* Variables and functions */
 int ENODEV ; 
 struct net_device* MASTER_TO_SLAVE (struct net_device*) ; 
 TYPE_2__* isdn_net_findif (char*) ; 
 int /*<<< orphan*/  isdn_net_hangup (struct net_device*) ; 

int
isdn_net_force_hangup(char *name)
{
	isdn_net_dev *p = isdn_net_findif(name);
	struct net_device *q;

	if (p) {
		if (p->local->isdn_device < 0)
			return 1;
		q = p->local->slave;
		/* If this interface has slaves, do a hangup for them also. */
		while (q) {
			isdn_net_hangup(q);
			q = MASTER_TO_SLAVE(q);
		}
		isdn_net_hangup(p->dev);
		return 0;
	}
	return -ENODEV;
}