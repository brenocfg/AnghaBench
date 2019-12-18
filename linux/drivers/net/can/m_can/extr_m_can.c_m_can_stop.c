#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct m_can_classdev {TYPE_1__ can; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  m_can_disable_all_interrupts (struct m_can_classdev*) ; 
 struct m_can_classdev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void m_can_stop(struct net_device *dev)
{
	struct m_can_classdev *cdev = netdev_priv(dev);

	/* disable all interrupts */
	m_can_disable_all_interrupts(cdev);

	/* set the state as STOPPED */
	cdev->can.state = CAN_STATE_STOPPED;
}