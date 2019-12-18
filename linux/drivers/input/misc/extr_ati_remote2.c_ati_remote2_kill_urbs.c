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
struct ati_remote2 {int /*<<< orphan*/ * urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ati_remote2_kill_urbs(struct ati_remote2 *ar2)
{
	usb_kill_urb(ar2->urb[1]);
	usb_kill_urb(ar2->urb[0]);
}