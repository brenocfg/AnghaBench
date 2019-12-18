#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ipr_res_addr {scalar_t__ bus; int target; } ;
struct TYPE_7__ {struct ipr_res_addr fd_res_addr; } ;
struct TYPE_6__ {int* fd_res_path; } ;
struct TYPE_8__ {TYPE_2__ error; TYPE_1__ error64; } ;
struct TYPE_9__ {TYPE_3__ u; } ;
struct ipr_hostrcb {TYPE_4__ hcam; TYPE_5__* ioa_cfg; } ;
struct TYPE_10__ {scalar_t__ sis64; } ;

/* Variables and functions */
 scalar_t__ IPR_MAX_NUM_BUSES ; 
 int IPR_MAX_NUM_TARGETS_PER_BUS ; 

__attribute__((used)) static inline int ipr_is_device(struct ipr_hostrcb *hostrcb)
{
	struct ipr_res_addr *res_addr;
	u8 *res_path;

	if (hostrcb->ioa_cfg->sis64) {
		res_path = &hostrcb->hcam.u.error64.fd_res_path[0];
		if ((res_path[0] == 0x00 || res_path[0] == 0x80 ||
		    res_path[0] == 0x81) && res_path[2] != 0xFF)
			return 1;
	} else {
		res_addr = &hostrcb->hcam.u.error.fd_res_addr;

		if ((res_addr->bus < IPR_MAX_NUM_BUSES) &&
		    (res_addr->target < (IPR_MAX_NUM_TARGETS_PER_BUS - 1)))
			return 1;
	}
	return 0;
}