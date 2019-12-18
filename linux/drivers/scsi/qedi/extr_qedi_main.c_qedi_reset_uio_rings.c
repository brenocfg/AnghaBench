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
struct qedi_uio_dev {int /*<<< orphan*/  ll2_buf_size; int /*<<< orphan*/  ll2_buf; int /*<<< orphan*/  ll2_ring_size; int /*<<< orphan*/  ll2_ring; struct qedi_uio_ctrl* uctrl; struct qedi_ctx* qedi; } ;
struct qedi_uio_ctrl {scalar_t__ host_rx_bd_cons; scalar_t__ hw_rx_bd_prod; scalar_t__ hw_rx_prod; scalar_t__ host_rx_cons; } ;
struct qedi_ctx {int /*<<< orphan*/  ll2_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qedi_reset_uio_rings(struct qedi_uio_dev *udev)
{
	struct qedi_ctx *qedi = NULL;
	struct qedi_uio_ctrl *uctrl = NULL;

	qedi = udev->qedi;
	uctrl = udev->uctrl;

	spin_lock_bh(&qedi->ll2_lock);
	uctrl->host_rx_cons = 0;
	uctrl->hw_rx_prod = 0;
	uctrl->hw_rx_bd_prod = 0;
	uctrl->host_rx_bd_cons = 0;

	memset(udev->ll2_ring, 0, udev->ll2_ring_size);
	memset(udev->ll2_buf, 0, udev->ll2_buf_size);
	spin_unlock_bh(&qedi->ll2_lock);
}