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
struct octeon_hcd {int frame_number; int /*<<< orphan*/  idle_pipes; } ;
struct cvmx_usb_pipe {int device_addr; int endpoint_num; int device_speed; int max_packet; int transfer_type; int transfer_dir; int interval; int next_tx_frame; int multi_count; int hub_device_addr; int hub_port; int split_sc_frame; int /*<<< orphan*/  node; scalar_t__ pid_toggle; int /*<<< orphan*/  transactions; int /*<<< orphan*/  flags; } ;
typedef  enum cvmx_usb_transfer { ____Placeholder_cvmx_usb_transfer } cvmx_usb_transfer ;
typedef  enum cvmx_usb_speed { ____Placeholder_cvmx_usb_speed } cvmx_usb_speed ;
typedef  enum cvmx_usb_direction { ____Placeholder_cvmx_usb_direction } cvmx_usb_direction ;

/* Variables and functions */
 int CVMX_USB_DIRECTION_OUT ; 
 int /*<<< orphan*/  CVMX_USB_PIPE_FLAGS_NEED_PING ; 
 int CVMX_USB_SPEED_HIGH ; 
 int CVMX_USB_TRANSFER_BULK ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ cvmx_usb_pipe_needs_split (struct octeon_hcd*,struct cvmx_usb_pipe*) ; 
 struct cvmx_usb_pipe* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cvmx_usb_pipe *cvmx_usb_open_pipe(struct octeon_hcd *usb,
						int device_addr,
						int endpoint_num,
						enum cvmx_usb_speed
							device_speed,
						int max_packet,
						enum cvmx_usb_transfer
							transfer_type,
						enum cvmx_usb_direction
							transfer_dir,
						int interval, int multi_count,
						int hub_device_addr,
						int hub_port)
{
	struct cvmx_usb_pipe *pipe;

	pipe = kzalloc(sizeof(*pipe), GFP_ATOMIC);
	if (!pipe)
		return NULL;
	if ((device_speed == CVMX_USB_SPEED_HIGH) &&
	    (transfer_dir == CVMX_USB_DIRECTION_OUT) &&
	    (transfer_type == CVMX_USB_TRANSFER_BULK))
		pipe->flags |= CVMX_USB_PIPE_FLAGS_NEED_PING;
	pipe->device_addr = device_addr;
	pipe->endpoint_num = endpoint_num;
	pipe->device_speed = device_speed;
	pipe->max_packet = max_packet;
	pipe->transfer_type = transfer_type;
	pipe->transfer_dir = transfer_dir;
	INIT_LIST_HEAD(&pipe->transactions);

	/*
	 * All pipes use interval to rate limit NAK processing. Force an
	 * interval if one wasn't supplied
	 */
	if (!interval)
		interval = 1;
	if (cvmx_usb_pipe_needs_split(usb, pipe)) {
		pipe->interval = interval * 8;
		/* Force start splits to be schedule on uFrame 0 */
		pipe->next_tx_frame = ((usb->frame_number + 7) & ~7) +
					pipe->interval;
	} else {
		pipe->interval = interval;
		pipe->next_tx_frame = usb->frame_number + pipe->interval;
	}
	pipe->multi_count = multi_count;
	pipe->hub_device_addr = hub_device_addr;
	pipe->hub_port = hub_port;
	pipe->pid_toggle = 0;
	pipe->split_sc_frame = -1;
	list_add_tail(&pipe->node, &usb->idle_pipes);

	/*
	 * We don't need to tell the hardware about this pipe yet since
	 * it doesn't have any submitted requests
	 */

	return pipe;
}