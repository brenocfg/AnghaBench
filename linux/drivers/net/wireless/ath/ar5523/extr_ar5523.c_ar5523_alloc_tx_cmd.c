#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ar5523_tx_cmd {TYPE_1__* urb_tx; int /*<<< orphan*/  buf_tx; int /*<<< orphan*/  done; struct ar5523* ar; } ;
struct ar5523 {int /*<<< orphan*/  dev; struct ar5523_tx_cmd tx_cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5523_MAX_TXCMDSZ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 

__attribute__((used)) static int ar5523_alloc_tx_cmd(struct ar5523 *ar)
{
	struct ar5523_tx_cmd *cmd = &ar->tx_cmd;

	cmd->ar = ar;
	init_completion(&cmd->done);

	cmd->urb_tx = usb_alloc_urb(0, GFP_KERNEL);
	if (!cmd->urb_tx)
		return -ENOMEM;
	cmd->buf_tx = usb_alloc_coherent(ar->dev, AR5523_MAX_TXCMDSZ,
					 GFP_KERNEL,
					 &cmd->urb_tx->transfer_dma);
	if (!cmd->buf_tx) {
		usb_free_urb(cmd->urb_tx);
		return -ENOMEM;
	}
	return 0;
}