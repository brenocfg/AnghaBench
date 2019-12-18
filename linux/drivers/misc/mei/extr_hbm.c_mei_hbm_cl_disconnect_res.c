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
struct mei_device {int dummy; } ;
struct mei_cl {scalar_t__ status; int /*<<< orphan*/  state; } ;
struct hbm_client_connect_response {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ MEI_CL_DISCONN_SUCCESS ; 
 int /*<<< orphan*/  MEI_FILE_DISCONNECT_REPLY ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*,scalar_t__) ; 

__attribute__((used)) static void mei_hbm_cl_disconnect_res(struct mei_device *dev, struct mei_cl *cl,
				      struct mei_hbm_cl_cmd *cmd)
{
	struct hbm_client_connect_response *rs =
		(struct hbm_client_connect_response *)cmd;

	cl_dbg(dev, cl, "hbm: disconnect response status=%d\n", rs->status);

	if (rs->status == MEI_CL_DISCONN_SUCCESS)
		cl->state = MEI_FILE_DISCONNECT_REPLY;
	cl->status = 0;
}