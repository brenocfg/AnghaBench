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
struct tm6000_core {int /*<<< orphan*/  urb_size; int /*<<< orphan*/ * urb_buffer; int /*<<< orphan*/ * urb_dma; int /*<<< orphan*/  udev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TM6000_NUM_URB_BUF ; 
 void* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tm6000_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tm6000_alloc_urb_buffers(struct tm6000_core *dev)
{
	int num_bufs = TM6000_NUM_URB_BUF;
	int i;

	if (dev->urb_buffer)
		return 0;

	dev->urb_buffer = kmalloc_array(num_bufs, sizeof(void *), GFP_KERNEL);
	if (!dev->urb_buffer)
		return -ENOMEM;

	dev->urb_dma = kmalloc_array(num_bufs, sizeof(dma_addr_t *),
				     GFP_KERNEL);
	if (!dev->urb_dma)
		return -ENOMEM;

	for (i = 0; i < num_bufs; i++) {
		dev->urb_buffer[i] = usb_alloc_coherent(
					dev->udev, dev->urb_size,
					GFP_KERNEL, &dev->urb_dma[i]);
		if (!dev->urb_buffer[i]) {
			tm6000_err("unable to allocate %i bytes for transfer buffer %i\n",
				    dev->urb_size, i);
			return -ENOMEM;
		}
		memset(dev->urb_buffer[i], 0, dev->urb_size);
	}

	return 0;
}