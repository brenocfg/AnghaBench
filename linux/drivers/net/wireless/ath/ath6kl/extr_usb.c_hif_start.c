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
struct ath6kl_usb {TYPE_1__* pipes; } ;
struct ath6kl {int dummy; } ;
struct TYPE_2__ {int urb_cnt_thresh; int urb_alloc; } ;

/* Variables and functions */
 int ATH6KL_USB_PIPE_TX_CTRL ; 
 int ATH6KL_USB_PIPE_TX_DATA_HP ; 
 struct ath6kl_usb* ath6kl_usb_priv (struct ath6kl*) ; 
 int /*<<< orphan*/  ath6kl_usb_start_recv_pipes (struct ath6kl_usb*) ; 

__attribute__((used)) static void hif_start(struct ath6kl *ar)
{
	struct ath6kl_usb *device = ath6kl_usb_priv(ar);
	int i;

	ath6kl_usb_start_recv_pipes(device);

	/* set the TX resource avail threshold for each TX pipe */
	for (i = ATH6KL_USB_PIPE_TX_CTRL;
	     i <= ATH6KL_USB_PIPE_TX_DATA_HP; i++) {
		device->pipes[i].urb_cnt_thresh =
		    device->pipes[i].urb_alloc / 2;
	}
}