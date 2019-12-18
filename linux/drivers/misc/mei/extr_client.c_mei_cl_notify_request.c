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
typedef  int /*<<< orphan*/  u8 ;
struct mei_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  ctrl_rd_list; int /*<<< orphan*/  hbm_f_ev_supported; } ;
struct mei_cl_cb {int /*<<< orphan*/  list; } ;
struct mei_cl {int status; int /*<<< orphan*/  notify_en; int /*<<< orphan*/  wait; struct mei_device* dev; } ;
struct file {int dummy; } ;
typedef  enum mei_cb_file_ops { ____Placeholder_mei_cb_file_ops } mei_cb_file_ops ;

/* Variables and functions */
 int EFAULT ; 
 int EINPROGRESS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MEI_CL_CONNECT_TIMEOUT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*) ; 
 int /*<<< orphan*/  cl_err (struct mei_device*,struct mei_cl*,char*,int) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mei_cl_cb* mei_cl_enqueue_ctrl_wr_cb (struct mei_cl*,int /*<<< orphan*/ ,int,struct file const*) ; 
 int /*<<< orphan*/  mei_cl_is_connected (struct mei_cl*) ; 
 int mei_cl_notify_req2fop (int /*<<< orphan*/ ) ; 
 scalar_t__ mei_hbm_cl_notify_req (struct mei_device*,struct mei_cl*,int /*<<< orphan*/ ) ; 
 scalar_t__ mei_hbuf_acquire (struct mei_device*) ; 
 int /*<<< orphan*/  mei_io_cb_free (struct mei_cl_cb*) ; 
 int /*<<< orphan*/  mei_secs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int mei_cl_notify_request(struct mei_cl *cl,
			  const struct file *fp, u8 request)
{
	struct mei_device *dev;
	struct mei_cl_cb *cb;
	enum mei_cb_file_ops fop_type;
	int rets;

	if (WARN_ON(!cl || !cl->dev))
		return -ENODEV;

	dev = cl->dev;

	if (!dev->hbm_f_ev_supported) {
		cl_dbg(dev, cl, "notifications not supported\n");
		return -EOPNOTSUPP;
	}

	if (!mei_cl_is_connected(cl))
		return -ENODEV;

	rets = pm_runtime_get(dev->dev);
	if (rets < 0 && rets != -EINPROGRESS) {
		pm_runtime_put_noidle(dev->dev);
		cl_err(dev, cl, "rpm: get failed %d\n", rets);
		return rets;
	}

	fop_type = mei_cl_notify_req2fop(request);
	cb = mei_cl_enqueue_ctrl_wr_cb(cl, 0, fop_type, fp);
	if (!cb) {
		rets = -ENOMEM;
		goto out;
	}

	if (mei_hbuf_acquire(dev)) {
		if (mei_hbm_cl_notify_req(dev, cl, request)) {
			rets = -ENODEV;
			goto out;
		}
		list_move_tail(&cb->list, &dev->ctrl_rd_list);
	}

	mutex_unlock(&dev->device_lock);
	wait_event_timeout(cl->wait,
			   cl->notify_en == request ||
			   cl->status ||
			   !mei_cl_is_connected(cl),
			   mei_secs_to_jiffies(MEI_CL_CONNECT_TIMEOUT));
	mutex_lock(&dev->device_lock);

	if (cl->notify_en != request && !cl->status)
		cl->status = -EFAULT;

	rets = cl->status;

out:
	cl_dbg(dev, cl, "rpm: autosuspend\n");
	pm_runtime_mark_last_busy(dev->dev);
	pm_runtime_put_autosuspend(dev->dev);

	mei_io_cb_free(cb);
	return rets;
}