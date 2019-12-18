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
typedef  int /*<<< orphan*/  u16 ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct f54_data {int /*<<< orphan*/  status_mutex; int /*<<< orphan*/  data_mutex; int /*<<< orphan*/  report_size; int /*<<< orphan*/  report_data; TYPE_1__* fn; int /*<<< orphan*/  cmd_done; scalar_t__ is_busy; int /*<<< orphan*/  input; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;
typedef  enum rmi_f54_report_type { ____Placeholder_rmi_f54_report_type } rmi_f54_report_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int F54_REPORT_NONE ; 
 int VB2_BUF_STATE_DONE ; 
 int VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmi_f54_get_report_size (struct f54_data*) ; 
 int rmi_f54_get_reptype (struct f54_data*,int /*<<< orphan*/ ) ; 
 int rmi_f54_request_report (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vb2_buffer_done (struct vb2_buffer*,int) ; 
 struct f54_data* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rmi_f54_buffer_queue(struct vb2_buffer *vb)
{
	struct f54_data *f54 = vb2_get_drv_priv(vb->vb2_queue);
	u16 *ptr;
	enum vb2_buffer_state state;
	enum rmi_f54_report_type reptype;
	int ret;

	mutex_lock(&f54->status_mutex);

	reptype = rmi_f54_get_reptype(f54, f54->input);
	if (reptype == F54_REPORT_NONE) {
		state = VB2_BUF_STATE_ERROR;
		goto done;
	}

	if (f54->is_busy) {
		state = VB2_BUF_STATE_ERROR;
		goto done;
	}

	ret = rmi_f54_request_report(f54->fn, reptype);
	if (ret) {
		dev_err(&f54->fn->dev, "Error requesting F54 report\n");
		state = VB2_BUF_STATE_ERROR;
		goto done;
	}

	/* get frame data */
	mutex_lock(&f54->data_mutex);

	while (f54->is_busy) {
		mutex_unlock(&f54->data_mutex);
		if (!wait_for_completion_timeout(&f54->cmd_done,
						 msecs_to_jiffies(1000))) {
			dev_err(&f54->fn->dev, "Timed out\n");
			state = VB2_BUF_STATE_ERROR;
			goto done;
		}
		mutex_lock(&f54->data_mutex);
	}

	ptr = vb2_plane_vaddr(vb, 0);
	if (!ptr) {
		dev_err(&f54->fn->dev, "Error acquiring frame ptr\n");
		state = VB2_BUF_STATE_ERROR;
		goto data_done;
	}

	memcpy(ptr, f54->report_data, f54->report_size);
	vb2_set_plane_payload(vb, 0, rmi_f54_get_report_size(f54));
	state = VB2_BUF_STATE_DONE;

data_done:
	mutex_unlock(&f54->data_mutex);
done:
	vb2_buffer_done(vb, state);
	mutex_unlock(&f54->status_mutex);
}