#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ar5523 {TYPE_1__* rx_cmd_urb; int /*<<< orphan*/  rx_cmd_buf; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5523_MAX_RXCMDSZ ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 

__attribute__((used)) static void ar5523_free_rx_cmd(struct ar5523 *ar)
{
	usb_free_coherent(ar->dev, AR5523_MAX_RXCMDSZ,
			  ar->rx_cmd_buf, ar->rx_cmd_urb->transfer_dma);
	usb_free_urb(ar->rx_cmd_urb);
}