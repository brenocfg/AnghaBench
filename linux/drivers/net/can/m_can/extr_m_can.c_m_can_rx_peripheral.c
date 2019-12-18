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
struct net_device {int dummy; } ;
struct m_can_classdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_can_enable_all_interrupts (struct m_can_classdev*) ; 
 int /*<<< orphan*/  m_can_rx_handler (struct net_device*,int) ; 
 struct m_can_classdev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int m_can_rx_peripheral(struct net_device *dev)
{
	struct m_can_classdev *cdev = netdev_priv(dev);

	m_can_rx_handler(dev, 1);

	m_can_enable_all_interrupts(cdev);

	return 0;
}