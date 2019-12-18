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
typedef  int /*<<< orphan*/  u16 ;
struct usbhs_priv {int dummy; } ;
struct usbhs_pipe {int /*<<< orphan*/  list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int usbhs_mod_is_host (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_pipe_clear (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_disable (struct usbhs_pipe*) ; 
 scalar_t__ usbhs_pipe_is_dir_in (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_name (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_number (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhs_pipe_sequence_data0 (struct usbhs_pipe*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 struct usbhs_pipe* usbhsp_get_pipe (struct usbhs_priv*,int) ; 
 int usbhsp_pipe_barrier (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhsp_pipe_buf_set (struct usbhs_pipe*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsp_pipe_cfg_set (struct usbhs_pipe*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * usbhsp_pipe_name ; 
 int /*<<< orphan*/  usbhsp_pipe_select (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhsp_setup_pipebuff (struct usbhs_pipe*) ; 
 scalar_t__ usbhsp_setup_pipecfg (struct usbhs_pipe*,int,int,int /*<<< orphan*/ *) ; 

struct usbhs_pipe *usbhs_pipe_malloc(struct usbhs_priv *priv,
				     int endpoint_type,
				     int dir_in)
{
	struct device *dev = usbhs_priv_to_dev(priv);
	struct usbhs_pipe *pipe;
	int is_host = usbhs_mod_is_host(priv);
	int ret;
	u16 pipecfg, pipebuf;

	pipe = usbhsp_get_pipe(priv, endpoint_type);
	if (!pipe) {
		dev_err(dev, "can't get pipe (%s)\n",
			usbhsp_pipe_name[endpoint_type]);
		return NULL;
	}

	INIT_LIST_HEAD(&pipe->list);

	usbhs_pipe_disable(pipe);

	/* make sure pipe is not busy */
	ret = usbhsp_pipe_barrier(pipe);
	if (ret < 0) {
		dev_err(dev, "pipe setup failed %d\n", usbhs_pipe_number(pipe));
		return NULL;
	}

	if (usbhsp_setup_pipecfg(pipe, is_host, dir_in, &pipecfg)) {
		dev_err(dev, "can't setup pipe\n");
		return NULL;
	}

	pipebuf  = usbhsp_setup_pipebuff(pipe);

	usbhsp_pipe_select(pipe);
	usbhsp_pipe_cfg_set(pipe, 0xFFFF, pipecfg);
	usbhsp_pipe_buf_set(pipe, 0xFFFF, pipebuf);
	usbhs_pipe_clear(pipe);

	usbhs_pipe_sequence_data0(pipe);

	dev_dbg(dev, "enable pipe %d : %s (%s)\n",
		usbhs_pipe_number(pipe),
		usbhs_pipe_name(pipe),
		usbhs_pipe_is_dir_in(pipe) ? "in" : "out");

	/*
	 * epnum / maxp are still not set to this pipe.
	 * call usbhs_pipe_config_update() after this function !!
	 */

	return pipe;
}