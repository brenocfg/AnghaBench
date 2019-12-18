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
struct statistics_block {int dummy; } ;
struct net_device {int dummy; } ;
struct bnx2 {int flags; int /*<<< orphan*/  timer; int /*<<< orphan*/  dev; int /*<<< orphan*/  temp_stats_blk; int /*<<< orphan*/  intr_sem; scalar_t__ current_interval; } ;

/* Variables and functions */
 int BNX2_FLAG_USING_MSI ; 
 int BNX2_FLAG_USING_MSIX ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bnx2_alloc_mem (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_del_napi (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_disable_int (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_enable_int (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_free_irq (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_free_mem (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_free_skbs (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_init_napi (struct bnx2*) ; 
 int bnx2_init_nic (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_napi_disable (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_napi_enable (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_release_firmware (struct bnx2*) ; 
 int bnx2_request_firmware (struct bnx2*) ; 
 int bnx2_request_irq (struct bnx2*) ; 
 int bnx2_setup_int_mode (struct bnx2*,int) ; 
 scalar_t__ bnx2_test_intr (struct bnx2*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int disable_msi ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 

__attribute__((used)) static int
bnx2_open(struct net_device *dev)
{
	struct bnx2 *bp = netdev_priv(dev);
	int rc;

	rc = bnx2_request_firmware(bp);
	if (rc < 0)
		goto out;

	netif_carrier_off(dev);

	bnx2_disable_int(bp);

	rc = bnx2_setup_int_mode(bp, disable_msi);
	if (rc)
		goto open_err;
	bnx2_init_napi(bp);
	bnx2_napi_enable(bp);
	rc = bnx2_alloc_mem(bp);
	if (rc)
		goto open_err;

	rc = bnx2_request_irq(bp);
	if (rc)
		goto open_err;

	rc = bnx2_init_nic(bp, 1);
	if (rc)
		goto open_err;

	mod_timer(&bp->timer, jiffies + bp->current_interval);

	atomic_set(&bp->intr_sem, 0);

	memset(bp->temp_stats_blk, 0, sizeof(struct statistics_block));

	bnx2_enable_int(bp);

	if (bp->flags & BNX2_FLAG_USING_MSI) {
		/* Test MSI to make sure it is working
		 * If MSI test fails, go back to INTx mode
		 */
		if (bnx2_test_intr(bp) != 0) {
			netdev_warn(bp->dev, "No interrupt was generated using MSI, switching to INTx mode. Please report this failure to the PCI maintainer and include system chipset information.\n");

			bnx2_disable_int(bp);
			bnx2_free_irq(bp);

			bnx2_setup_int_mode(bp, 1);

			rc = bnx2_init_nic(bp, 0);

			if (!rc)
				rc = bnx2_request_irq(bp);

			if (rc) {
				del_timer_sync(&bp->timer);
				goto open_err;
			}
			bnx2_enable_int(bp);
		}
	}
	if (bp->flags & BNX2_FLAG_USING_MSI)
		netdev_info(dev, "using MSI\n");
	else if (bp->flags & BNX2_FLAG_USING_MSIX)
		netdev_info(dev, "using MSIX\n");

	netif_tx_start_all_queues(dev);
out:
	return rc;

open_err:
	bnx2_napi_disable(bp);
	bnx2_free_skbs(bp);
	bnx2_free_irq(bp);
	bnx2_free_mem(bp);
	bnx2_del_napi(bp);
	bnx2_release_firmware(bp);
	goto out;
}