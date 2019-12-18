#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ break_control; } ;
struct nfcmrvl_private {TYPE_3__ config; TYPE_2__* ndev; } ;
struct nci_uart {TYPE_5__* tty; scalar_t__ drv_data; } ;
struct TYPE_10__ {TYPE_4__* ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* break_ctl ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__* nfc_dev; } ;
struct TYPE_6__ {scalar_t__ fw_download_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void nfcmrvl_nci_uart_tx_start(struct nci_uart *nu)
{
	struct nfcmrvl_private *priv = (struct nfcmrvl_private *)nu->drv_data;

	if (priv->ndev->nfc_dev->fw_download_in_progress)
		return;

	/* Remove BREAK to wake up the NFCC */
	if (priv->config.break_control && nu->tty->ops->break_ctl) {
		nu->tty->ops->break_ctl(nu->tty, 0);
		usleep_range(3000, 5000);
	}
}