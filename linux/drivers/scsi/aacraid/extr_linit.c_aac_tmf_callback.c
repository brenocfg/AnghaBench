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
struct fib {scalar_t__ hw_fib_va; } ;
struct aac_hba_resp {int service_response; } ;
struct TYPE_2__ {struct aac_hba_resp err; } ;
struct aac_native_hba {TYPE_1__ resp; } ;
struct aac_hba_map_info {int reset_state; } ;

/* Variables and functions */
#define  HBA_RESP_SVCRES_TMF_COMPLETE 131 
#define  HBA_RESP_SVCRES_TMF_LUN_INVALID 130 
#define  HBA_RESP_SVCRES_TMF_REJECTED 129 
#define  HBA_RESP_SVCRES_TMF_SUCCEEDED 128 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 

void aac_tmf_callback(void *context, struct fib *fibptr)
{
	struct aac_hba_resp *err =
		&((struct aac_native_hba *)fibptr->hw_fib_va)->resp.err;
	struct aac_hba_map_info *info = context;
	int res;

	switch (err->service_response) {
	case HBA_RESP_SVCRES_TMF_REJECTED:
		res = -1;
		break;
	case HBA_RESP_SVCRES_TMF_LUN_INVALID:
		res = 0;
		break;
	case HBA_RESP_SVCRES_TMF_COMPLETE:
	case HBA_RESP_SVCRES_TMF_SUCCEEDED:
		res = 0;
		break;
	default:
		res = -2;
		break;
	}
	aac_fib_complete(fibptr);

	info->reset_state = res;
}