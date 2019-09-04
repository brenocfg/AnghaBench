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
struct mei_hbm_cl_cmd {int dummy; } ;
struct mei_device {scalar_t__ dev_state; int /*<<< orphan*/  bus_rescan_work; } ;
struct mei_cl {int /*<<< orphan*/  status; int /*<<< orphan*/  me_cl; int /*<<< orphan*/  state; } ;
struct hbm_client_connect_response {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ MEI_CL_CONN_NOT_FOUND ; 
 scalar_t__ MEI_CL_CONN_SUCCESS ; 
 scalar_t__ MEI_DEV_ENABLED ; 
 int /*<<< orphan*/  MEI_FILE_CONNECTED ; 
 int /*<<< orphan*/  MEI_FILE_DISCONNECT_REPLY ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_cl_conn_status_str (scalar_t__) ; 
 int /*<<< orphan*/  mei_cl_conn_status_to_errno (scalar_t__) ; 
 int /*<<< orphan*/  mei_me_cl_del (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mei_hbm_cl_connect_res(struct mei_device *dev, struct mei_cl *cl,
				   struct mei_hbm_cl_cmd *cmd)
{
	struct hbm_client_connect_response *rs =
		(struct hbm_client_connect_response *)cmd;

	cl_dbg(dev, cl, "hbm: connect response status=%s\n",
			mei_cl_conn_status_str(rs->status));

	if (rs->status == MEI_CL_CONN_SUCCESS)
		cl->state = MEI_FILE_CONNECTED;
	else {
		cl->state = MEI_FILE_DISCONNECT_REPLY;
		if (rs->status == MEI_CL_CONN_NOT_FOUND) {
			mei_me_cl_del(dev, cl->me_cl);
			if (dev->dev_state == MEI_DEV_ENABLED)
				schedule_work(&dev->bus_rescan_work);
		}
	}
	cl->status = mei_cl_conn_status_to_errno(rs->status);
}