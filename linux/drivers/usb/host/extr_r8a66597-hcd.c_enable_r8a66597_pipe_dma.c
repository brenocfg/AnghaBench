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
struct urb {int /*<<< orphan*/  pipe; } ;
struct r8a66597_pipe_info {unsigned short pipenum; scalar_t__ type; scalar_t__ epnum; scalar_t__ dir_in; } ;
struct r8a66597_pipe {int /*<<< orphan*/  fifoctr; struct r8a66597_pipe_info info; int /*<<< orphan*/  fifosel; } ;
struct r8a66597_device {int dma_map; TYPE_2__* udev; } ;
struct r8a66597 {int dma_map; TYPE_1__* pdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ on_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCLR ; 
 unsigned short CURPIPE ; 
 scalar_t__ R8A66597_INT ; 
 int R8A66597_MAX_DMA_CHANNEL ; 
 scalar_t__ USB_ENDPOINT_DIR_MASK ; 
 int /*<<< orphan*/  cfifo_change (struct r8a66597*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned short mbw_value (struct r8a66597*) ; 
 int /*<<< orphan*/  r8a66597_bset (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_mdfy (struct r8a66597*,unsigned short,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_reg_wait (struct r8a66597*,int /*<<< orphan*/ ,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  set_pipe_reg_addr (struct r8a66597_pipe*,int) ; 
 int /*<<< orphan*/  usb_pipedevice (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_r8a66597_pipe_dma(struct r8a66597 *r8a66597,
				     struct r8a66597_device *dev,
				     struct r8a66597_pipe *pipe,
				     struct urb *urb)
{
	int i;
	struct r8a66597_pipe_info *info = &pipe->info;
	unsigned short mbw = mbw_value(r8a66597);

	/* pipe dma is only for external controlles */
	if (r8a66597->pdata->on_chip)
		return;

	if ((pipe->info.pipenum != 0) && (info->type != R8A66597_INT)) {
		for (i = 0; i < R8A66597_MAX_DMA_CHANNEL; i++) {
			if ((r8a66597->dma_map & (1 << i)) != 0)
				continue;

			dev_info(&dev->udev->dev,
				 "address %d, EndpointAddress 0x%02x use "
				 "DMA FIFO\n", usb_pipedevice(urb->pipe),
				 info->dir_in ?
				 	USB_ENDPOINT_DIR_MASK + info->epnum
					: info->epnum);

			r8a66597->dma_map |= 1 << i;
			dev->dma_map |= 1 << i;
			set_pipe_reg_addr(pipe, i);

			cfifo_change(r8a66597, 0);
			r8a66597_mdfy(r8a66597, mbw | pipe->info.pipenum,
				      mbw | CURPIPE, pipe->fifosel);

			r8a66597_reg_wait(r8a66597, pipe->fifosel, CURPIPE,
					  pipe->info.pipenum);
			r8a66597_bset(r8a66597, BCLR, pipe->fifoctr);
			break;
		}
	}
}