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
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hif_detach_htc (struct ath6kl*) ; 

__attribute__((used)) static int ath6kl_usb_power_off(struct ath6kl *ar)
{
	hif_detach_htc(ar);
	return 0;
}