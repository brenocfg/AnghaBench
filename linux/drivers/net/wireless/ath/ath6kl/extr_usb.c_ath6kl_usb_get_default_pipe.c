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
typedef  int /*<<< orphan*/  u8 ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_USB_PIPE_RX_CTRL ; 
 int /*<<< orphan*/  ATH6KL_USB_PIPE_TX_CTRL ; 

__attribute__((used)) static void ath6kl_usb_get_default_pipe(struct ath6kl *ar,
					u8 *ul_pipe, u8 *dl_pipe)
{
	*ul_pipe = ATH6KL_USB_PIPE_TX_CTRL;
	*dl_pipe = ATH6KL_USB_PIPE_RX_CTRL;
}