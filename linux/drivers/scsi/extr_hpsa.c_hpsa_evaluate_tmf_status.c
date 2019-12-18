#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ctlr_info {TYPE_2__* pdev; } ;
struct CommandList {TYPE_1__* err_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int ScsiStatus; } ;

/* Variables and functions */
#define  CISS_TMF_COMPLETE 134 
#define  CISS_TMF_FAILED 133 
#define  CISS_TMF_INVALID_FRAME 132 
#define  CISS_TMF_NOT_SUPPORTED 131 
#define  CISS_TMF_OVERLAPPED_TAG 130 
#define  CISS_TMF_SUCCESS 129 
#define  CISS_TMF_WRONG_LUN 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int hpsa_evaluate_tmf_status(struct ctlr_info *h,
					struct CommandList *cp)
{
	u8 tmf_status = cp->err_info->ScsiStatus;

	switch (tmf_status) {
	case CISS_TMF_COMPLETE:
		/*
		 * CISS_TMF_COMPLETE never happens, instead,
		 * ei->CommandStatus == 0 for this case.
		 */
	case CISS_TMF_SUCCESS:
		return 0;
	case CISS_TMF_INVALID_FRAME:
	case CISS_TMF_NOT_SUPPORTED:
	case CISS_TMF_FAILED:
	case CISS_TMF_WRONG_LUN:
	case CISS_TMF_OVERLAPPED_TAG:
		break;
	default:
		dev_warn(&h->pdev->dev, "Unknown TMF status: 0x%02x\n",
				tmf_status);
		break;
	}
	return -tmf_status;
}