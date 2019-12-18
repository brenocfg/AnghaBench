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
struct can_berr_counter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __m_can_get_berr_counter (struct net_device const*,struct can_berr_counter*) ; 
 int m_can_clk_start (struct m_can_classdev*) ; 
 int /*<<< orphan*/  m_can_clk_stop (struct m_can_classdev*) ; 
 struct m_can_classdev* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int m_can_get_berr_counter(const struct net_device *dev,
				  struct can_berr_counter *bec)
{
	struct m_can_classdev *cdev = netdev_priv(dev);
	int err;

	err = m_can_clk_start(cdev);
	if (err)
		return err;

	__m_can_get_berr_counter(dev, bec);

	m_can_clk_stop(cdev);

	return 0;
}