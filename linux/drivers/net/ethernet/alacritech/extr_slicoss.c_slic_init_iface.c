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
struct slic_shmem {int /*<<< orphan*/  isr_paddr; } ;
struct TYPE_3__ {int pending; } ;
struct slic_device {int /*<<< orphan*/  napi; int /*<<< orphan*/  netdev; TYPE_2__* pdev; int /*<<< orphan*/  link_lock; int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; TYPE_1__ upr_list; struct slic_shmem shmem; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  SLIC_ICR_INT_OFF ; 
 int /*<<< orphan*/  SLIC_ICR_INT_ON ; 
 int /*<<< orphan*/  SLIC_REG_ICR ; 
 int /*<<< orphan*/  SLIC_REG_INTAGG ; 
 int /*<<< orphan*/  SLIC_REG_ISP ; 
 int /*<<< orphan*/  SLIC_REG_ISR ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct slic_device*) ; 
 int /*<<< orphan*/  slic_card_reset (struct slic_device*) ; 
 int /*<<< orphan*/  slic_flush_write (struct slic_device*) ; 
 int /*<<< orphan*/  slic_free_rx_queue (struct slic_device*) ; 
 int /*<<< orphan*/  slic_free_shmem (struct slic_device*) ; 
 int /*<<< orphan*/  slic_free_stat_queue (struct slic_device*) ; 
 int /*<<< orphan*/  slic_free_tx_queue (struct slic_device*) ; 
 int slic_handle_link_change (struct slic_device*) ; 
 int slic_init_rx_queue (struct slic_device*) ; 
 int slic_init_shmem (struct slic_device*) ; 
 int slic_init_stat_queue (struct slic_device*) ; 
 int slic_init_tx_queue (struct slic_device*) ; 
 int /*<<< orphan*/  slic_irq ; 
 int slic_load_firmware (struct slic_device*) ; 
 int slic_load_rcvseq_firmware (struct slic_device*) ; 
 int /*<<< orphan*/  slic_set_link_autoneg (struct slic_device*) ; 
 int /*<<< orphan*/  slic_set_mac_address (struct slic_device*) ; 
 int /*<<< orphan*/  slic_write (struct slic_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int slic_init_iface(struct slic_device *sdev)
{
	struct slic_shmem *sm = &sdev->shmem;
	int err;

	sdev->upr_list.pending = false;

	err = slic_init_shmem(sdev);
	if (err) {
		netdev_err(sdev->netdev, "failed to init shared memory\n");
		return err;
	}

	err = slic_load_firmware(sdev);
	if (err) {
		netdev_err(sdev->netdev, "failed to load firmware\n");
		goto free_sm;
	}

	err = slic_load_rcvseq_firmware(sdev);
	if (err) {
		netdev_err(sdev->netdev,
			   "failed to load firmware for receive sequencer\n");
		goto free_sm;
	}

	slic_write(sdev, SLIC_REG_ICR, SLIC_ICR_INT_OFF);
	slic_flush_write(sdev);
	mdelay(1);

	err = slic_init_rx_queue(sdev);
	if (err) {
		netdev_err(sdev->netdev, "failed to init rx queue: %u\n", err);
		goto free_sm;
	}

	err = slic_init_tx_queue(sdev);
	if (err) {
		netdev_err(sdev->netdev, "failed to init tx queue: %u\n", err);
		goto free_rxq;
	}

	err = slic_init_stat_queue(sdev);
	if (err) {
		netdev_err(sdev->netdev, "failed to init status queue: %u\n",
			   err);
		goto free_txq;
	}

	slic_write(sdev, SLIC_REG_ISP, lower_32_bits(sm->isr_paddr));
	napi_enable(&sdev->napi);
	/* disable irq mitigation */
	slic_write(sdev, SLIC_REG_INTAGG, 0);
	slic_write(sdev, SLIC_REG_ISR, 0);
	slic_flush_write(sdev);

	slic_set_mac_address(sdev);

	spin_lock_bh(&sdev->link_lock);
	sdev->duplex = DUPLEX_UNKNOWN;
	sdev->speed = SPEED_UNKNOWN;
	spin_unlock_bh(&sdev->link_lock);

	slic_set_link_autoneg(sdev);

	err = request_irq(sdev->pdev->irq, slic_irq, IRQF_SHARED, DRV_NAME,
			  sdev);
	if (err) {
		netdev_err(sdev->netdev, "failed to request irq: %u\n", err);
		goto disable_napi;
	}

	slic_write(sdev, SLIC_REG_ICR, SLIC_ICR_INT_ON);
	slic_flush_write(sdev);
	/* request initial link status */
	err = slic_handle_link_change(sdev);
	if (err)
		netdev_warn(sdev->netdev,
			    "failed to set initial link state: %u\n", err);
	return 0;

disable_napi:
	napi_disable(&sdev->napi);
	slic_free_stat_queue(sdev);
free_txq:
	slic_free_tx_queue(sdev);
free_rxq:
	slic_free_rx_queue(sdev);
free_sm:
	slic_free_shmem(sdev);
	slic_card_reset(sdev);

	return err;
}