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
struct work_struct {int dummy; } ;
struct hinic_rx_mode_work {int /*<<< orphan*/  rx_mode; } ;
struct hinic_dev {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dev_mc_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dev_uc_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_mac_addr ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  hinic_port_set_rx_mode (struct hinic_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct hinic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  remove_mac_addr ; 
 struct hinic_dev* rx_mode_work_to_nic_dev (struct hinic_rx_mode_work*) ; 
 struct hinic_rx_mode_work* work_to_rx_mode_work (struct work_struct*) ; 

__attribute__((used)) static void set_rx_mode(struct work_struct *work)
{
	struct hinic_rx_mode_work *rx_mode_work = work_to_rx_mode_work(work);
	struct hinic_dev *nic_dev = rx_mode_work_to_nic_dev(rx_mode_work);

	netif_info(nic_dev, drv, nic_dev->netdev, "set rx mode work\n");

	hinic_port_set_rx_mode(nic_dev, rx_mode_work->rx_mode);

	__dev_uc_sync(nic_dev->netdev, add_mac_addr, remove_mac_addr);
	__dev_mc_sync(nic_dev->netdev, add_mac_addr, remove_mac_addr);
}