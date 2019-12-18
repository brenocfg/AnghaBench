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
struct usb_hcd {scalar_t__ hcd_priv; } ;
struct isp116x {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct isp116x *hcd_to_isp116x(struct usb_hcd *hcd)
{
	return (struct isp116x *)(hcd->hcd_priv);
}