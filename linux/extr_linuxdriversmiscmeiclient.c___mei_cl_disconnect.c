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
struct mei_device {int /*<<< orphan*/  device_lock; } ;
struct mei_cl_cb {int dummy; } ;
struct mei_cl {scalar_t__ state; int status; int /*<<< orphan*/  wait; struct mei_device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIME ; 
 int /*<<< orphan*/  MEI_CL_CONNECT_TIMEOUT ; 
 scalar_t__ MEI_FILE_DISCONNECTED ; 
 scalar_t__ MEI_FILE_DISCONNECTING ; 
 scalar_t__ MEI_FILE_DISCONNECT_REPLY ; 
 int /*<<< orphan*/  MEI_FOP_DISCONNECT ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*) ; 
 int /*<<< orphan*/  cl_err (struct mei_device*,struct mei_cl*,char*) ; 
 struct mei_cl_cb* mei_cl_enqueue_ctrl_wr_cb (struct mei_cl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mei_cl_send_disconnect (struct mei_cl*,struct mei_cl_cb*) ; 
 int /*<<< orphan*/  mei_cl_set_disconnected (struct mei_cl*) ; 
 scalar_t__ mei_hbuf_acquire (struct mei_device*) ; 
 int /*<<< orphan*/  mei_io_cb_free (struct mei_cl_cb*) ; 
 int /*<<< orphan*/  mei_secs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __mei_cl_disconnect(struct mei_cl *cl)
{
	struct mei_device *dev;
	struct mei_cl_cb *cb;
	int rets;

	dev = cl->dev;

	cl->state = MEI_FILE_DISCONNECTING;

	cb = mei_cl_enqueue_ctrl_wr_cb(cl, 0, MEI_FOP_DISCONNECT, NULL);
	if (!cb) {
		rets = -ENOMEM;
		goto out;
	}

	if (mei_hbuf_acquire(dev)) {
		rets = mei_cl_send_disconnect(cl, cb);
		if (rets) {
			cl_err(dev, cl, "failed to disconnect.\n");
			goto out;
		}
	}

	mutex_unlock(&dev->device_lock);
	wait_event_timeout(cl->wait,
			   cl->state == MEI_FILE_DISCONNECT_REPLY ||
			   cl->state == MEI_FILE_DISCONNECTED,
			   mei_secs_to_jiffies(MEI_CL_CONNECT_TIMEOUT));
	mutex_lock(&dev->device_lock);

	rets = cl->status;
	if (cl->state != MEI_FILE_DISCONNECT_REPLY &&
	    cl->state != MEI_FILE_DISCONNECTED) {
		cl_dbg(dev, cl, "timeout on disconnect from FW client.\n");
		rets = -ETIME;
	}

out:
	/* we disconnect also on error */
	mei_cl_set_disconnected(cl);
	if (!rets)
		cl_dbg(dev, cl, "successfully disconnected from FW client.\n");

	mei_io_cb_free(cb);
	return rets;
}