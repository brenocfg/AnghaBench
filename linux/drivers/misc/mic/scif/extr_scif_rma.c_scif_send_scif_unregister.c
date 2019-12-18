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
typedef  scalar_t__ u64 ;
struct scifmsg {scalar_t__* payload; int /*<<< orphan*/  src; int /*<<< orphan*/  uop; } ;
struct TYPE_2__ {scalar_t__ vaddr; } ;
struct scif_window {TYPE_1__ alloc_handle; } ;
struct scif_endpt {int /*<<< orphan*/  remote_dev; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_UNREGISTER ; 
 int scif_nodeqp_send (int /*<<< orphan*/ ,struct scifmsg*) ; 

__attribute__((used)) static int scif_send_scif_unregister(struct scif_endpt *ep,
				     struct scif_window *window)
{
	struct scifmsg msg;

	msg.uop = SCIF_UNREGISTER;
	msg.src = ep->port;
	msg.payload[0] = window->alloc_handle.vaddr;
	msg.payload[1] = (u64)window;
	return scif_nodeqp_send(ep->remote_dev, &msg);
}