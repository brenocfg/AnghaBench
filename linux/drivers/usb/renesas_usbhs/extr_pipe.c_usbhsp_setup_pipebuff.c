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
struct renesas_usbhs_driver_pipe_config {int bufsize; int bufnum; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,int) ; 
 int usbhs_pipe_number (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 struct renesas_usbhs_driver_pipe_config* usbhsp_get_pipe_config (struct usbhs_priv*,int) ; 

__attribute__((used)) static u16 usbhsp_setup_pipebuff(struct usbhs_pipe *pipe)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct device *dev = usbhs_priv_to_dev(priv);
	int pipe_num = usbhs_pipe_number(pipe);
	u16 buff_size;
	u16 bufnmb;
	u16 bufnmb_cnt;
	struct renesas_usbhs_driver_pipe_config *pipe_config =
					usbhsp_get_pipe_config(priv, pipe_num);

	/*
	 * PIPEBUF
	 *
	 * see
	 *  - "Register Descriptions" - "PIPEBUF" register
	 *  - "Features"  - "Pipe configuration"
	 *  - "Operation" - "FIFO Buffer Memory"
	 *  - "Operation" - "Pipe Control"
	 */
	buff_size = pipe_config->bufsize;
	bufnmb = pipe_config->bufnum;

	/* change buff_size to register value */
	bufnmb_cnt = (buff_size / 64) - 1;

	dev_dbg(dev, "pipe : %d : buff_size 0x%x: bufnmb 0x%x\n",
		pipe_num, buff_size, bufnmb);

	return	(0x1f & bufnmb_cnt)	<< 10 |
		(0xff & bufnmb)		<<  0;
}