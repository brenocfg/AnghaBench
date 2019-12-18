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
struct usb_device {TYPE_1__* bus; } ;
struct urb {int /*<<< orphan*/  sg; int /*<<< orphan*/  num_sgs; int /*<<< orphan*/  stream_id; } ;
struct uas_dev_info {unsigned int data_in_pipe; unsigned int data_out_pipe; scalar_t__ use_streams; struct usb_device* udev; } ;
struct uas_cmd_info {int /*<<< orphan*/  uas_tag; } ;
struct TYPE_4__ {int /*<<< orphan*/  sgl; int /*<<< orphan*/  nents; } ;
struct scsi_data_buffer {TYPE_2__ table; int /*<<< orphan*/  length; } ;
struct scsi_cmnd {struct scsi_data_buffer sdb; int /*<<< orphan*/  SCp; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_3__ {scalar_t__ sg_tablesize; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  uas_data_cmplt ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_cmnd*) ; 

__attribute__((used)) static struct urb *uas_alloc_data_urb(struct uas_dev_info *devinfo, gfp_t gfp,
				      struct scsi_cmnd *cmnd,
				      enum dma_data_direction dir)
{
	struct usb_device *udev = devinfo->udev;
	struct uas_cmd_info *cmdinfo = (void *)&cmnd->SCp;
	struct urb *urb = usb_alloc_urb(0, gfp);
	struct scsi_data_buffer *sdb = &cmnd->sdb;
	unsigned int pipe = (dir == DMA_FROM_DEVICE)
		? devinfo->data_in_pipe : devinfo->data_out_pipe;

	if (!urb)
		goto out;
	usb_fill_bulk_urb(urb, udev, pipe, NULL, sdb->length,
			  uas_data_cmplt, cmnd);
	if (devinfo->use_streams)
		urb->stream_id = cmdinfo->uas_tag;
	urb->num_sgs = udev->bus->sg_tablesize ? sdb->table.nents : 0;
	urb->sg = sdb->table.sgl;
 out:
	return urb;
}