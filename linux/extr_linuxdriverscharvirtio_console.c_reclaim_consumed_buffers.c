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
struct port_buffer {int dummy; } ;
struct port {int outvq_full; int /*<<< orphan*/  out_vq; int /*<<< orphan*/  portdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_buf (struct port_buffer*,int) ; 
 struct port_buffer* virtqueue_get_buf (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void reclaim_consumed_buffers(struct port *port)
{
	struct port_buffer *buf;
	unsigned int len;

	if (!port->portdev) {
		/* Device has been unplugged.  vqs are already gone. */
		return;
	}
	while ((buf = virtqueue_get_buf(port->out_vq, &len))) {
		free_buf(buf, false);
		port->outvq_full = false;
	}
}