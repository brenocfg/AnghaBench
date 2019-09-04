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
struct port_buffer {scalar_t__ offset; scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  bytes_discarded; } ;
struct port {int /*<<< orphan*/  dev; int /*<<< orphan*/ * inbuf; int /*<<< orphan*/  in_vq; TYPE_1__ stats; int /*<<< orphan*/  portdev; } ;

/* Variables and functions */
 scalar_t__ add_inbuf (int /*<<< orphan*/ ,struct port_buffer*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  free_buf (struct port_buffer*,int) ; 
 struct port_buffer* get_inbuf (struct port*) ; 

__attribute__((used)) static void discard_port_data(struct port *port)
{
	struct port_buffer *buf;
	unsigned int err;

	if (!port->portdev) {
		/* Device has been unplugged.  vqs are already gone. */
		return;
	}
	buf = get_inbuf(port);

	err = 0;
	while (buf) {
		port->stats.bytes_discarded += buf->len - buf->offset;
		if (add_inbuf(port->in_vq, buf) < 0) {
			err++;
			free_buf(buf, false);
		}
		port->inbuf = NULL;
		buf = get_inbuf(port);
	}
	if (err)
		dev_warn(port->dev, "Errors adding %d buffers back to vq\n",
			 err);
}