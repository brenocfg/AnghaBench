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
struct usbhs_priv {int dummy; } ;
struct usbhs_pipe {int dummy; } ;
struct usbhs_fifo {int /*<<< orphan*/  ctr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCLR ; 
 int usbhs_pipe_is_accessible (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_is_dcp (struct usbhs_pipe*) ; 
 scalar_t__ usbhs_pipe_is_dir_in (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_write (struct usbhs_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usbhsf_fifo_barrier (struct usbhs_priv*,struct usbhs_fifo*) ; 

__attribute__((used)) static void usbhsf_fifo_clear(struct usbhs_pipe *pipe,
			      struct usbhs_fifo *fifo)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	int ret = 0;

	if (!usbhs_pipe_is_dcp(pipe)) {
		/*
		 * This driver checks the pipe condition first to avoid -EBUSY
		 * from usbhsf_fifo_barrier() if the pipe is RX direction and
		 * empty.
		 */
		if (usbhs_pipe_is_dir_in(pipe))
			ret = usbhs_pipe_is_accessible(pipe);
		if (!ret)
			ret = usbhsf_fifo_barrier(priv, fifo);
	}

	/*
	 * if non-DCP pipe, this driver should set BCLR when
	 * usbhsf_fifo_barrier() returns 0.
	 */
	if (!ret)
		usbhs_write(priv, fifo->ctr, BCLR);
}