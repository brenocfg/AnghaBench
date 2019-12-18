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
struct usb_hcd {int dummy; } ;
struct fotg210_hcd {int periodic_size; } ;

/* Variables and functions */
 int fotg210_read_frame_index (struct fotg210_hcd*) ; 
 struct fotg210_hcd* hcd_to_fotg210 (struct usb_hcd*) ; 

__attribute__((used)) static int fotg210_get_frame(struct usb_hcd *hcd)
{
	struct fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);

	return (fotg210_read_frame_index(fotg210) >> 3) %
		fotg210->periodic_size;
}