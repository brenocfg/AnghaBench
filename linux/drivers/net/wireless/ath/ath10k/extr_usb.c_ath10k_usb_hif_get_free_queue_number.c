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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ath10k_usb {TYPE_1__* pipes; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  urb_cnt; } ;

/* Variables and functions */
 struct ath10k_usb* ath10k_usb_priv (struct ath10k*) ; 

__attribute__((used)) static u16 ath10k_usb_hif_get_free_queue_number(struct ath10k *ar, u8 pipe_id)
{
	struct ath10k_usb *ar_usb = ath10k_usb_priv(ar);

	return ar_usb->pipes[pipe_id].urb_cnt;
}