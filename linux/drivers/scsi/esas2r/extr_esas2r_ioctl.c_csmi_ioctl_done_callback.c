#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct atto_csmi_get_scsi_addr {int /*<<< orphan*/  path_id; int /*<<< orphan*/  target_id; } ;
struct atto_csmi_get_driver_info {int /*<<< orphan*/  release_rev; int /*<<< orphan*/  build_rev; int /*<<< orphan*/  minor_rev; int /*<<< orphan*/  major_rev; int /*<<< orphan*/  name; } ;
union atto_ioctl_csmi {struct atto_csmi_get_scsi_addr scsi_addr; struct atto_csmi_get_driver_info drvr_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  csmi_status; } ;
struct TYPE_5__ {TYPE_1__ csmi; } ;
struct TYPE_6__ {TYPE_2__ ioctl_rsp; } ;
struct esas2r_request {TYPE_3__ func_rsp; int /*<<< orphan*/  target_id; } ;
struct esas2r_adapter {int dummy; } ;
struct atto_csmi {int control_code; int /*<<< orphan*/  status; } ;

/* Variables and functions */
#define  CSMI_CC_GET_DRVR_INFO 129 
#define  CSMI_CC_GET_SCSI_ADDR 128 
 int /*<<< orphan*/  CSMI_STS_SUCCESS ; 
 int /*<<< orphan*/  ESAS2R_MAJOR_REV ; 
 int /*<<< orphan*/  ESAS2R_MINOR_REV ; 
 int /*<<< orphan*/  ESAS2R_VERSION_STR ; 
 scalar_t__ esas2r_buffered_ioctl ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csmi_ioctl_done_callback(struct esas2r_adapter *a,
				     struct esas2r_request *rq, void *context)
{
	struct atto_csmi *ci = (struct atto_csmi *)context;
	union atto_ioctl_csmi *ioctl_csmi =
		(union atto_ioctl_csmi *)esas2r_buffered_ioctl;

	switch (ci->control_code) {
	case CSMI_CC_GET_DRVR_INFO:
	{
		struct atto_csmi_get_driver_info *gdi =
			&ioctl_csmi->drvr_info;

		strcpy(gdi->name, ESAS2R_VERSION_STR);

		gdi->major_rev = ESAS2R_MAJOR_REV;
		gdi->minor_rev = ESAS2R_MINOR_REV;
		gdi->build_rev = 0;
		gdi->release_rev = 0;
		break;
	}

	case CSMI_CC_GET_SCSI_ADDR:
	{
		struct atto_csmi_get_scsi_addr *gsa = &ioctl_csmi->scsi_addr;

		if (le32_to_cpu(rq->func_rsp.ioctl_rsp.csmi.csmi_status) ==
		    CSMI_STS_SUCCESS) {
			gsa->target_id = rq->target_id;
			gsa->path_id = 0;
		}

		break;
	}
	}

	ci->status = le32_to_cpu(rq->func_rsp.ioctl_rsp.csmi.csmi_status);
}