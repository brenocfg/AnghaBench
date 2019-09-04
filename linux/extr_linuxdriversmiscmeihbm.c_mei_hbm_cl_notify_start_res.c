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
struct mei_cl {int notify_en; int /*<<< orphan*/  status; } ;
struct hbm_notification_response {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MEI_HBMS_ALREADY_STARTED ; 
 scalar_t__ MEI_HBMS_SUCCESS ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*,scalar_t__) ; 

__attribute__((used)) static void mei_hbm_cl_notify_start_res(struct mei_device *dev,
					struct mei_cl *cl,
					struct mei_hbm_cl_cmd *cmd)
{
	struct hbm_notification_response *rs =
		(struct hbm_notification_response *)cmd;

	cl_dbg(dev, cl, "hbm: notify start response status=%d\n", rs->status);

	if (rs->status == MEI_HBMS_SUCCESS ||
	    rs->status == MEI_HBMS_ALREADY_STARTED) {
		cl->notify_en = true;
		cl->status = 0;
	} else {
		cl->status = -EINVAL;
	}
}