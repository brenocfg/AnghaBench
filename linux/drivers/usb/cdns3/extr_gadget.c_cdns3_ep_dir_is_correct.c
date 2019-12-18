#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_endpoint_descriptor {int dummy; } ;
struct TYPE_3__ {scalar_t__ dir_out; scalar_t__ dir_in; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;
struct cdns3_endpoint {TYPE_2__ endpoint; } ;

/* Variables and functions */
 scalar_t__ usb_endpoint_dir_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_dir_out (struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static int cdns3_ep_dir_is_correct(struct usb_endpoint_descriptor *desc,
				   struct cdns3_endpoint *priv_ep)
{
	return (priv_ep->endpoint.caps.dir_in && usb_endpoint_dir_in(desc)) ||
	       (priv_ep->endpoint.caps.dir_out && usb_endpoint_dir_out(desc));
}