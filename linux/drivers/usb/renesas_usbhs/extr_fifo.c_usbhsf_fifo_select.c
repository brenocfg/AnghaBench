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
typedef  int u16 ;
struct usbhs_priv {int dummy; } ;
struct usbhs_pipe {int dummy; } ;
struct usbhs_fifo {int /*<<< orphan*/  sel; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int MBW_32 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usbhs_dcp_dir_for_host (struct usbhs_pipe*,int) ; 
 scalar_t__ usbhs_mod_is_host (struct usbhs_priv*) ; 
 scalar_t__ usbhs_pipe_is_busy (struct usbhs_pipe*) ; 
 scalar_t__ usbhs_pipe_is_dcp (struct usbhs_pipe*) ; 
 int usbhs_pipe_number (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_select_fifo (struct usbhs_pipe*,struct usbhs_fifo*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 int usbhs_read (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_write (struct usbhs_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ usbhsf_fifo_is_busy (struct usbhs_fifo*) ; 

__attribute__((used)) static int usbhsf_fifo_select(struct usbhs_pipe *pipe,
			      struct usbhs_fifo *fifo,
			      int write)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct device *dev = usbhs_priv_to_dev(priv);
	int timeout = 1024;
	u16 mask = ((1 << 5) | 0xF);		/* mask of ISEL | CURPIPE */
	u16 base = usbhs_pipe_number(pipe);	/* CURPIPE */

	if (usbhs_pipe_is_busy(pipe) ||
	    usbhsf_fifo_is_busy(fifo))
		return -EBUSY;

	if (usbhs_pipe_is_dcp(pipe)) {
		base |= (1 == write) << 5;	/* ISEL */

		if (usbhs_mod_is_host(priv))
			usbhs_dcp_dir_for_host(pipe, write);
	}

	/* "base" will be used below  */
	usbhs_write(priv, fifo->sel, base | MBW_32);

	/* check ISEL and CURPIPE value */
	while (timeout--) {
		if (base == (mask & usbhs_read(priv, fifo->sel))) {
			usbhs_pipe_select_fifo(pipe, fifo);
			return 0;
		}
		udelay(10);
	}

	dev_err(dev, "fifo select error\n");

	return -EIO;
}