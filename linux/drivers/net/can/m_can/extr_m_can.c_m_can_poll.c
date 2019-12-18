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
struct napi_struct {struct net_device* dev; } ;
struct m_can_classdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_can_enable_all_interrupts (struct m_can_classdev*) ; 
 int m_can_rx_handler (struct net_device*,int) ; 
 int /*<<< orphan*/  napi_complete_done (struct napi_struct*,int) ; 
 struct m_can_classdev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int m_can_poll(struct napi_struct *napi, int quota)
{
	struct net_device *dev = napi->dev;
	struct m_can_classdev *cdev = netdev_priv(dev);
	int work_done;

	work_done = m_can_rx_handler(dev, quota);
	if (work_done < quota) {
		napi_complete_done(napi, work_done);
		m_can_enable_all_interrupts(cdev);
	}

	return work_done;
}