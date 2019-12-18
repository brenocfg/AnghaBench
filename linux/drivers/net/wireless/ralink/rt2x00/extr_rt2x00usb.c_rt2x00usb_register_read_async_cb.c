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
struct urb {int /*<<< orphan*/  status; struct rt2x00_async_read_data* context; } ;
struct rt2x00_async_read_data {TYPE_1__* rt2x00dev; int /*<<< orphan*/  reg; scalar_t__ (* callback ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  anchor; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct rt2x00_async_read_data*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void rt2x00usb_register_read_async_cb(struct urb *urb)
{
	struct rt2x00_async_read_data *rd = urb->context;
	if (rd->callback(rd->rt2x00dev, urb->status, le32_to_cpu(rd->reg))) {
		usb_anchor_urb(urb, rd->rt2x00dev->anchor);
		if (usb_submit_urb(urb, GFP_ATOMIC) < 0) {
			usb_unanchor_urb(urb);
			kfree(rd);
		}
	} else
		kfree(rd);
}