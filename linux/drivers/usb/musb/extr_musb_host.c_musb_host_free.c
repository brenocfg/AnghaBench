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
struct musb {int /*<<< orphan*/  hcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_put_hcd (int /*<<< orphan*/ ) ; 

void musb_host_free(struct musb *musb)
{
	usb_put_hcd(musb->hcd);
}