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
struct dwc2_hsotg {int dummy; } ;
struct dwc2_hcd_urb {int packet_count; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  iso_descs ; 
 struct dwc2_hcd_urb* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (struct dwc2_hcd_urb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dwc2_hcd_urb *dwc2_hcd_urb_alloc(struct dwc2_hsotg *hsotg,
					       int iso_desc_count,
					       gfp_t mem_flags)
{
	struct dwc2_hcd_urb *urb;

	urb = kzalloc(struct_size(urb, iso_descs, iso_desc_count), mem_flags);
	if (urb)
		urb->packet_count = iso_desc_count;
	return urb;
}