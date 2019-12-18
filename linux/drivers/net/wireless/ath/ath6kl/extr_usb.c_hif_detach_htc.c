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
struct ath6kl_usb {int dummy; } ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_usb_flush_all (struct ath6kl_usb*) ; 
 struct ath6kl_usb* ath6kl_usb_priv (struct ath6kl*) ; 

__attribute__((used)) static void hif_detach_htc(struct ath6kl *ar)
{
	struct ath6kl_usb *device = ath6kl_usb_priv(ar);

	ath6kl_usb_flush_all(device);
}