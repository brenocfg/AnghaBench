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
struct usb_dmac_chan {scalar_t__ descs_allocated; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ USB_DMAC_INITIAL_NR_DESC ; 
 int /*<<< orphan*/  USB_DMAC_INITIAL_NR_SG ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 struct usb_dmac_chan* to_usb_dmac_chan (struct dma_chan*) ; 
 int usb_dmac_desc_alloc (struct usb_dmac_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dmac_desc_free (struct usb_dmac_chan*) ; 

__attribute__((used)) static int usb_dmac_alloc_chan_resources(struct dma_chan *chan)
{
	struct usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	int ret;

	while (uchan->descs_allocated < USB_DMAC_INITIAL_NR_DESC) {
		ret = usb_dmac_desc_alloc(uchan, USB_DMAC_INITIAL_NR_SG,
					  GFP_KERNEL);
		if (ret < 0) {
			usb_dmac_desc_free(uchan);
			return ret;
		}
		uchan->descs_allocated++;
	}

	return pm_runtime_get_sync(chan->device->dev);
}