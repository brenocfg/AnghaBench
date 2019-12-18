#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sysdev; scalar_t__ uses_pio_for_control; } ;
struct usb_hcd {scalar_t__ localmem_pool; TYPE_2__ self; } ;
struct usb_ctrlrequest {int dummy; } ;
struct urb {void* setup_packet; int transfer_flags; int transfer_buffer_length; int num_sgs; int num_mapped_sgs; void* transfer_buffer; void* transfer_dma; TYPE_3__* dev; struct scatterlist* sg; TYPE_1__* ep; void* setup_dma; } ;
struct scatterlist {int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_6__ {int /*<<< orphan*/  bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int URB_DMA_MAP_PAGE ; 
 int URB_DMA_MAP_SG ; 
 int URB_DMA_MAP_SINGLE ; 
 int URB_DMA_SG_COMBINED ; 
 int URB_MAP_LOCAL ; 
 int URB_NO_TRANSFER_DMA_MAP ; 
 int URB_SETUP_MAP_LOCAL ; 
 int URB_SETUP_MAP_SINGLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 void* dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int) ; 
 void* dma_map_single (int /*<<< orphan*/ ,void*,int,int) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 int hcd_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,void**,int,int) ; 
 scalar_t__ hcd_uses_dma (struct usb_hcd*) ; 
 scalar_t__ is_vmalloc_addr (void*) ; 
 scalar_t__ object_is_on_stack (void*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 scalar_t__ usb_endpoint_xfer_control (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_xfer_isoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_hcd_unmap_urb_for_dma (struct usb_hcd*,struct urb*) ; 
 scalar_t__ usb_urb_dir_in (struct urb*) ; 

int usb_hcd_map_urb_for_dma(struct usb_hcd *hcd, struct urb *urb,
			    gfp_t mem_flags)
{
	enum dma_data_direction dir;
	int ret = 0;

	/* Map the URB's buffers for DMA access.
	 * Lower level HCD code should use *_dma exclusively,
	 * unless it uses pio or talks to another transport,
	 * or uses the provided scatter gather list for bulk.
	 */

	if (usb_endpoint_xfer_control(&urb->ep->desc)) {
		if (hcd->self.uses_pio_for_control)
			return ret;
		if (hcd_uses_dma(hcd)) {
			if (is_vmalloc_addr(urb->setup_packet)) {
				WARN_ONCE(1, "setup packet is not dma capable\n");
				return -EAGAIN;
			} else if (object_is_on_stack(urb->setup_packet)) {
				WARN_ONCE(1, "setup packet is on stack\n");
				return -EAGAIN;
			}

			urb->setup_dma = dma_map_single(
					hcd->self.sysdev,
					urb->setup_packet,
					sizeof(struct usb_ctrlrequest),
					DMA_TO_DEVICE);
			if (dma_mapping_error(hcd->self.sysdev,
						urb->setup_dma))
				return -EAGAIN;
			urb->transfer_flags |= URB_SETUP_MAP_SINGLE;
		} else if (hcd->localmem_pool) {
			ret = hcd_alloc_coherent(
					urb->dev->bus, mem_flags,
					&urb->setup_dma,
					(void **)&urb->setup_packet,
					sizeof(struct usb_ctrlrequest),
					DMA_TO_DEVICE);
			if (ret)
				return ret;
			urb->transfer_flags |= URB_SETUP_MAP_LOCAL;
		}
	}

	dir = usb_urb_dir_in(urb) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	if (urb->transfer_buffer_length != 0
	    && !(urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP)) {
		if (hcd_uses_dma(hcd)) {
			if (urb->num_sgs) {
				int n;

				/* We don't support sg for isoc transfers ! */
				if (usb_endpoint_xfer_isoc(&urb->ep->desc)) {
					WARN_ON(1);
					return -EINVAL;
				}

				n = dma_map_sg(
						hcd->self.sysdev,
						urb->sg,
						urb->num_sgs,
						dir);
				if (n <= 0)
					ret = -EAGAIN;
				else
					urb->transfer_flags |= URB_DMA_MAP_SG;
				urb->num_mapped_sgs = n;
				if (n != urb->num_sgs)
					urb->transfer_flags |=
							URB_DMA_SG_COMBINED;
			} else if (urb->sg) {
				struct scatterlist *sg = urb->sg;
				urb->transfer_dma = dma_map_page(
						hcd->self.sysdev,
						sg_page(sg),
						sg->offset,
						urb->transfer_buffer_length,
						dir);
				if (dma_mapping_error(hcd->self.sysdev,
						urb->transfer_dma))
					ret = -EAGAIN;
				else
					urb->transfer_flags |= URB_DMA_MAP_PAGE;
			} else if (is_vmalloc_addr(urb->transfer_buffer)) {
				WARN_ONCE(1, "transfer buffer not dma capable\n");
				ret = -EAGAIN;
			} else if (object_is_on_stack(urb->transfer_buffer)) {
				WARN_ONCE(1, "transfer buffer is on stack\n");
				ret = -EAGAIN;
			} else {
				urb->transfer_dma = dma_map_single(
						hcd->self.sysdev,
						urb->transfer_buffer,
						urb->transfer_buffer_length,
						dir);
				if (dma_mapping_error(hcd->self.sysdev,
						urb->transfer_dma))
					ret = -EAGAIN;
				else
					urb->transfer_flags |= URB_DMA_MAP_SINGLE;
			}
		} else if (hcd->localmem_pool) {
			ret = hcd_alloc_coherent(
					urb->dev->bus, mem_flags,
					&urb->transfer_dma,
					&urb->transfer_buffer,
					urb->transfer_buffer_length,
					dir);
			if (ret == 0)
				urb->transfer_flags |= URB_MAP_LOCAL;
		}
		if (ret && (urb->transfer_flags & (URB_SETUP_MAP_SINGLE |
				URB_SETUP_MAP_LOCAL)))
			usb_hcd_unmap_urb_for_dma(hcd, urb);
	}
	return ret;
}