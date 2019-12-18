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
struct hif_device_usb {int /*<<< orphan*/  regout_submitted; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ath9k_hif_usb_alloc_reg_in_urbs (struct hif_device_usb*) ; 
 scalar_t__ ath9k_hif_usb_alloc_rx_urbs (struct hif_device_usb*) ; 
 scalar_t__ ath9k_hif_usb_alloc_tx_urbs (struct hif_device_usb*) ; 
 int /*<<< orphan*/  ath9k_hif_usb_dealloc_rx_urbs (struct hif_device_usb*) ; 
 int /*<<< orphan*/  ath9k_hif_usb_dealloc_tx_urbs (struct hif_device_usb*) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_hif_usb_alloc_urbs(struct hif_device_usb *hif_dev)
{
	/* Register Write */
	init_usb_anchor(&hif_dev->regout_submitted);

	/* TX */
	if (ath9k_hif_usb_alloc_tx_urbs(hif_dev) < 0)
		goto err;

	/* RX */
	if (ath9k_hif_usb_alloc_rx_urbs(hif_dev) < 0)
		goto err_rx;

	/* Register Read */
	if (ath9k_hif_usb_alloc_reg_in_urbs(hif_dev) < 0)
		goto err_reg;

	return 0;
err_reg:
	ath9k_hif_usb_dealloc_rx_urbs(hif_dev);
err_rx:
	ath9k_hif_usb_dealloc_tx_urbs(hif_dev);
err:
	return -ENOMEM;
}