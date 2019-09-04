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
struct ushc_data {int /*<<< orphan*/  mmc; int /*<<< orphan*/  csw; int /*<<< orphan*/  cbw; int /*<<< orphan*/  int_data; int /*<<< orphan*/  cbw_urb; int /*<<< orphan*/  data_urb; int /*<<< orphan*/  csw_urb; int /*<<< orphan*/  int_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ushc_clean_up(struct ushc_data *ushc)
{
	usb_free_urb(ushc->int_urb);
	usb_free_urb(ushc->csw_urb);
	usb_free_urb(ushc->data_urb);
	usb_free_urb(ushc->cbw_urb);

	kfree(ushc->int_data);
	kfree(ushc->cbw);
	kfree(ushc->csw);

	mmc_free_host(ushc->mmc);
}