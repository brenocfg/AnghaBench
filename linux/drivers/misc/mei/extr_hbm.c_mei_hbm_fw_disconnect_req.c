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
struct mei_device {int dummy; } ;
struct mei_cl_cb {int dummy; } ;
struct mei_cl {scalar_t__ timer_count; int /*<<< orphan*/  state; } ;
struct hbm_client_connect_request {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MEI_FILE_DISCONNECTING ; 
 int /*<<< orphan*/  MEI_FOP_DISCONNECT_RSP ; 
 int /*<<< orphan*/  cl_warn (struct mei_device*,struct mei_cl*,char*) ; 
 struct mei_cl_cb* mei_cl_enqueue_ctrl_wr_cb (struct mei_cl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mei_cl* mei_hbm_cl_find_by_cmd (struct mei_device*,struct hbm_client_connect_request*) ; 

__attribute__((used)) static int mei_hbm_fw_disconnect_req(struct mei_device *dev,
		struct hbm_client_connect_request *disconnect_req)
{
	struct mei_cl *cl;
	struct mei_cl_cb *cb;

	cl = mei_hbm_cl_find_by_cmd(dev, disconnect_req);
	if (cl) {
		cl_warn(dev, cl, "fw disconnect request received\n");
		cl->state = MEI_FILE_DISCONNECTING;
		cl->timer_count = 0;

		cb = mei_cl_enqueue_ctrl_wr_cb(cl, 0, MEI_FOP_DISCONNECT_RSP,
					       NULL);
		if (!cb)
			return -ENOMEM;
	}
	return 0;
}