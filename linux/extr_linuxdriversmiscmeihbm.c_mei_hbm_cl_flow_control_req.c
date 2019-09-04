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
struct mei_cl {int dummy; } ;
struct hbm_flow_control {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  MEI_FLOW_CONTROL_CMD ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*) ; 
 int mei_hbm_cl_write (struct mei_device*,struct mei_cl*,int /*<<< orphan*/ ,struct hbm_flow_control*,int) ; 

int mei_hbm_cl_flow_control_req(struct mei_device *dev, struct mei_cl *cl)
{
	struct hbm_flow_control req;

	cl_dbg(dev, cl, "sending flow control\n");
	return mei_hbm_cl_write(dev, cl, MEI_FLOW_CONTROL_CMD,
				&req, sizeof(req));
}