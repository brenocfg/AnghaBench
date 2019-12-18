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
struct port100 {TYPE_1__* in_urb; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  port100_recv_ack ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int port100_submit_urb_for_ack(struct port100 *dev, gfp_t flags)
{
	dev->in_urb->complete = port100_recv_ack;

	return usb_submit_urb(dev->in_urb, flags);
}