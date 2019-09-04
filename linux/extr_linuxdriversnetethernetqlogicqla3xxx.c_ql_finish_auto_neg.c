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
struct ql3_adapter {int mac_index; int /*<<< orphan*/  ndev; int /*<<< orphan*/  flags; int /*<<< orphan*/  port_link_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  LS_UP ; 
 int /*<<< orphan*/  QL_LINK_MASTER ; 
 int /*<<< orphan*/  QL_PHY_GIO_SEM_MASK ; 
 int QL_RESOURCE_BITS_BASE_CODE ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct ql3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  netif_printk (struct ql3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_auto_neg_error (struct ql3_adapter*) ; 
 scalar_t__ ql_get_link_speed (struct ql3_adapter*) ; 
 scalar_t__ ql_is_link_full_dup (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_is_neg_pause (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_mac_cfg_full_dup (struct ql3_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  ql_mac_cfg_gig (struct ql3_adapter*,int) ; 
 int /*<<< orphan*/  ql_mac_cfg_pause (struct ql3_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_mac_cfg_soft_reset (struct ql3_adapter*,int) ; 
 int /*<<< orphan*/  ql_mac_enable (struct ql3_adapter*,int) ; 
 scalar_t__ ql_port_start (struct ql3_adapter*) ; 
 scalar_t__ ql_sem_spinlock (struct ql3_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql3_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql_finish_auto_neg(struct ql3_adapter *qdev)
{

	if (ql_sem_spinlock(qdev, QL_PHY_GIO_SEM_MASK,
		(QL_RESOURCE_BITS_BASE_CODE | (qdev->mac_index) *
			 2) << 7))
		return -1;

	if (!ql_auto_neg_error(qdev)) {
		if (test_bit(QL_LINK_MASTER, &qdev->flags)) {
			/* configure the MAC */
			netif_printk(qdev, link, KERN_DEBUG, qdev->ndev,
				     "Configuring link\n");
			ql_mac_cfg_soft_reset(qdev, 1);
			ql_mac_cfg_gig(qdev,
				       (ql_get_link_speed
					(qdev) ==
					SPEED_1000));
			ql_mac_cfg_full_dup(qdev,
					    ql_is_link_full_dup
					    (qdev));
			ql_mac_cfg_pause(qdev,
					 ql_is_neg_pause
					 (qdev));
			ql_mac_cfg_soft_reset(qdev, 0);

			/* enable the MAC */
			netif_printk(qdev, link, KERN_DEBUG, qdev->ndev,
				     "Enabling mac\n");
			ql_mac_enable(qdev, 1);
		}

		qdev->port_link_state = LS_UP;
		netif_start_queue(qdev->ndev);
		netif_carrier_on(qdev->ndev);
		netif_info(qdev, link, qdev->ndev,
			   "Link is up at %d Mbps, %s duplex\n",
			   ql_get_link_speed(qdev),
			   ql_is_link_full_dup(qdev) ? "full" : "half");

	} else {	/* Remote error detected */

		if (test_bit(QL_LINK_MASTER, &qdev->flags)) {
			netif_printk(qdev, link, KERN_DEBUG, qdev->ndev,
				     "Remote error detected. Calling ql_port_start()\n");
			/*
			 * ql_port_start() is shared code and needs
			 * to lock the PHY on it's own.
			 */
			ql_sem_unlock(qdev, QL_PHY_GIO_SEM_MASK);
			if (ql_port_start(qdev))	/* Restart port */
				return -1;
			return 0;
		}
	}
	ql_sem_unlock(qdev, QL_PHY_GIO_SEM_MASK);
	return 0;
}