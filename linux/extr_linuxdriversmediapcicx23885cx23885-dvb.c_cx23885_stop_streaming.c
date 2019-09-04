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
struct vb2_queue {struct cx23885_tsport* drv_priv; } ;
struct cx23885_tsport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx23885_cancel_buffers (struct cx23885_tsport*) ; 

__attribute__((used)) static void cx23885_stop_streaming(struct vb2_queue *q)
{
	struct cx23885_tsport *port = q->drv_priv;

	cx23885_cancel_buffers(port);
}