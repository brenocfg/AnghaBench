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
struct ath6kl_usb {int /*<<< orphan*/ * pipes; } ;

/* Variables and functions */
 int ATH6KL_USB_PIPE_MAX ; 
 int /*<<< orphan*/  ath6kl_usb_free_pipe_resources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_usb_cleanup_pipe_resources(struct ath6kl_usb *ar_usb)
{
	int i;

	for (i = 0; i < ATH6KL_USB_PIPE_MAX; i++)
		ath6kl_usb_free_pipe_resources(&ar_usb->pipes[i]);
}