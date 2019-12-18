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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
struct TYPE_5__ {int status; } ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct vub300_mmc_host {int datasize; unsigned char* padded_buffer; TYPE_1__ sg_request; TYPE_3__ sg_transfer_timer; int /*<<< orphan*/  command_res_urb; int /*<<< orphan*/  command_out_urb; int /*<<< orphan*/  udev; scalar_t__ large_usb_packets; int /*<<< orphan*/  data_out_ep; } ;
struct mmc_data {int bytes_xfered; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct mmc_command {int error; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_3__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int usb_sg_init (TYPE_1__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sg_wait (TYPE_1__*) ; 
 unsigned int usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ ) ; 
 int vub300_usb_bulk_msg (struct vub300_mmc_host*,unsigned int,unsigned char*,int,int*,int) ; 

__attribute__((used)) static int __command_write_data(struct vub300_mmc_host *vub300,
				struct mmc_command *cmd, struct mmc_data *data)
{
	/* cmd_mutex is held by vub300_cmndwork_thread */
	unsigned pipe = usb_sndbulkpipe(vub300->udev, vub300->data_out_ep);
	int linear_length = vub300->datasize;
	int modulo_64_length = linear_length & 0x003F;
	int modulo_512_length = linear_length & 0x01FF;
	if (linear_length < 64) {
		int result;
		int actual_length;
		sg_copy_to_buffer(data->sg, data->sg_len,
				  vub300->padded_buffer,
				  sizeof(vub300->padded_buffer));
		memset(vub300->padded_buffer + linear_length, 0,
		       sizeof(vub300->padded_buffer) - linear_length);
		result = vub300_usb_bulk_msg(vub300, pipe, vub300->padded_buffer,
					     sizeof(vub300->padded_buffer),
					     &actual_length, 2000 +
					     (sizeof(vub300->padded_buffer) /
					      16384));
		if (result < 0) {
			cmd->error = result;
			data->bytes_xfered = 0;
		} else {
			data->bytes_xfered = vub300->datasize;
		}
	} else if ((!vub300->large_usb_packets && (0 < modulo_64_length)) ||
		    (vub300->large_usb_packets && (64 > modulo_512_length))
		) {		/* don't you just love these work-rounds */
		int padded_length = ((63 + linear_length) >> 6) << 6;
		u8 *buf = kmalloc(padded_length, GFP_KERNEL);
		if (buf) {
			int result;
			int actual_length;
			sg_copy_to_buffer(data->sg, data->sg_len, buf,
					  padded_length);
			memset(buf + linear_length, 0,
			       padded_length - linear_length);
			result =
				vub300_usb_bulk_msg(vub300, pipe, buf,
						    padded_length, &actual_length,
						    2000 + padded_length / 16384);
			kfree(buf);
			if (result < 0) {
				cmd->error = result;
				data->bytes_xfered = 0;
			} else {
				data->bytes_xfered = vub300->datasize;
			}
		} else {
			cmd->error = -ENOMEM;
			data->bytes_xfered = 0;
		}
	} else {		/* no data padding required */
		int result;
		unsigned char buf[64 * 4];
		sg_copy_to_buffer(data->sg, data->sg_len, buf, sizeof(buf));
		result = usb_sg_init(&vub300->sg_request, vub300->udev,
				     pipe, 0, data->sg,
				     data->sg_len, 0, GFP_KERNEL);
		if (result < 0) {
			usb_unlink_urb(vub300->command_out_urb);
			usb_unlink_urb(vub300->command_res_urb);
			cmd->error = result;
			data->bytes_xfered = 0;
		} else {
			vub300->sg_transfer_timer.expires =
				jiffies + msecs_to_jiffies(2000 +
							   linear_length / 16384);
			add_timer(&vub300->sg_transfer_timer);
			usb_sg_wait(&vub300->sg_request);
			if (cmd->error) {
				data->bytes_xfered = 0;
			} else {
				del_timer(&vub300->sg_transfer_timer);
				if (vub300->sg_request.status < 0) {
					cmd->error = vub300->sg_request.status;
					data->bytes_xfered = 0;
				} else {
					data->bytes_xfered = vub300->datasize;
				}
			}
		}
	}
	return linear_length;
}