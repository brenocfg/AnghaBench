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
struct sisusb_usb_data {int numobufs; int /*<<< orphan*/ * urbstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  SU_URB_ALLOC ; 

__attribute__((used)) static void sisusb_free_outbuf(struct sisusb_usb_data *sisusb, int index)
{
	if ((index >= 0) && (index < sisusb->numobufs))
		sisusb->urbstatus[index] &= ~SU_URB_ALLOC;
}