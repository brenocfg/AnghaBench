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
typedef  int /*<<< orphan*/  u16 ;
struct urb {int /*<<< orphan*/  pipe; } ;
struct r8a66597_device {int /*<<< orphan*/  address; } ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 struct r8a66597_device* get_urb_to_r8a66597_dev (struct r8a66597*,struct urb*) ; 
 scalar_t__ usb_pipedevice (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 get_urb_to_r8a66597_addr(struct r8a66597 *r8a66597, struct urb *urb)
{
	struct r8a66597_device *dev = get_urb_to_r8a66597_dev(r8a66597, urb);

	return (usb_pipedevice(urb->pipe) == 0) ? 0 : dev->address;
}