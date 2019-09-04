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
struct mei_device {int /*<<< orphan*/  dev; } ;
struct mei_cl_cb {int /*<<< orphan*/  list; } ;
struct mei_cl {scalar_t__ rx_flow_ctrl_creds; int /*<<< orphan*/  rd_pending; int /*<<< orphan*/  me_cl; struct mei_device* dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOTTY ; 
 int /*<<< orphan*/  MEI_FOP_READ ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*) ; 
 int /*<<< orphan*/  cl_err (struct mei_device*,struct mei_cl*,char*,...) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mei_cl_cb* mei_cl_enqueue_ctrl_wr_cb (struct mei_cl*,size_t,int /*<<< orphan*/ ,struct file const*) ; 
 int /*<<< orphan*/  mei_cl_is_connected (struct mei_cl*) ; 
 scalar_t__ mei_cl_is_fixed_address (struct mei_cl*) ; 
 int mei_hbm_cl_flow_control_req (struct mei_device*,struct mei_cl*) ; 
 scalar_t__ mei_hbuf_acquire (struct mei_device*) ; 
 int /*<<< orphan*/  mei_io_cb_free (struct mei_cl_cb*) ; 
 int /*<<< orphan*/  mei_me_cl_is_active (int /*<<< orphan*/ ) ; 
 int pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 

int mei_cl_read_start(struct mei_cl *cl, size_t length, const struct file *fp)
{
	struct mei_device *dev;
	struct mei_cl_cb *cb;
	int rets;

	if (WARN_ON(!cl || !cl->dev))
		return -ENODEV;

	dev = cl->dev;

	if (!mei_cl_is_connected(cl))
		return -ENODEV;

	if (!mei_me_cl_is_active(cl->me_cl)) {
		cl_err(dev, cl, "no such me client\n");
		return  -ENOTTY;
	}

	if (mei_cl_is_fixed_address(cl))
		return 0;

	/* HW currently supports only one pending read */
	if (cl->rx_flow_ctrl_creds)
		return -EBUSY;

	cb = mei_cl_enqueue_ctrl_wr_cb(cl, length, MEI_FOP_READ, fp);
	if (!cb)
		return -ENOMEM;

	rets = pm_runtime_get(dev->dev);
	if (rets < 0 && rets != -EINPROGRESS) {
		pm_runtime_put_noidle(dev->dev);
		cl_err(dev, cl, "rpm: get failed %d\n", rets);
		goto nortpm;
	}

	rets = 0;
	if (mei_hbuf_acquire(dev)) {
		rets = mei_hbm_cl_flow_control_req(dev, cl);
		if (rets < 0)
			goto out;

		list_move_tail(&cb->list, &cl->rd_pending);
	}
	cl->rx_flow_ctrl_creds++;

out:
	cl_dbg(dev, cl, "rpm: autosuspend\n");
	pm_runtime_mark_last_busy(dev->dev);
	pm_runtime_put_autosuspend(dev->dev);
nortpm:
	if (rets)
		mei_io_cb_free(cb);

	return rets;
}