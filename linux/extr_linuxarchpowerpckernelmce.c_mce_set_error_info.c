#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  link_error_type; int /*<<< orphan*/  ra_error_type; int /*<<< orphan*/  user_error_type; int /*<<< orphan*/  tlb_error_type; int /*<<< orphan*/  erat_error_type; int /*<<< orphan*/  slb_error_type; int /*<<< orphan*/  ue_error_type; } ;
struct mce_error_info {int error_type; TYPE_9__ u; } ;
struct TYPE_16__ {int /*<<< orphan*/  link_error_type; } ;
struct TYPE_15__ {int /*<<< orphan*/  ra_error_type; } ;
struct TYPE_14__ {int /*<<< orphan*/  user_error_type; } ;
struct TYPE_13__ {int /*<<< orphan*/  tlb_error_type; } ;
struct TYPE_12__ {int /*<<< orphan*/  erat_error_type; } ;
struct TYPE_11__ {int /*<<< orphan*/  slb_error_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  ue_error_type; } ;
struct TYPE_17__ {TYPE_7__ link_error; TYPE_6__ ra_error; TYPE_5__ user_error; TYPE_4__ tlb_error; TYPE_3__ erat_error; TYPE_2__ slb_error; TYPE_1__ ue_error; } ;
struct machine_check_event {int error_type; TYPE_8__ u; } ;

/* Variables and functions */
#define  MCE_ERROR_TYPE_ERAT 135 
#define  MCE_ERROR_TYPE_LINK 134 
#define  MCE_ERROR_TYPE_RA 133 
#define  MCE_ERROR_TYPE_SLB 132 
#define  MCE_ERROR_TYPE_TLB 131 
#define  MCE_ERROR_TYPE_UE 130 
#define  MCE_ERROR_TYPE_UNKNOWN 129 
#define  MCE_ERROR_TYPE_USER 128 

__attribute__((used)) static void mce_set_error_info(struct machine_check_event *mce,
			       struct mce_error_info *mce_err)
{
	mce->error_type = mce_err->error_type;
	switch (mce_err->error_type) {
	case MCE_ERROR_TYPE_UE:
		mce->u.ue_error.ue_error_type = mce_err->u.ue_error_type;
		break;
	case MCE_ERROR_TYPE_SLB:
		mce->u.slb_error.slb_error_type = mce_err->u.slb_error_type;
		break;
	case MCE_ERROR_TYPE_ERAT:
		mce->u.erat_error.erat_error_type = mce_err->u.erat_error_type;
		break;
	case MCE_ERROR_TYPE_TLB:
		mce->u.tlb_error.tlb_error_type = mce_err->u.tlb_error_type;
		break;
	case MCE_ERROR_TYPE_USER:
		mce->u.user_error.user_error_type = mce_err->u.user_error_type;
		break;
	case MCE_ERROR_TYPE_RA:
		mce->u.ra_error.ra_error_type = mce_err->u.ra_error_type;
		break;
	case MCE_ERROR_TYPE_LINK:
		mce->u.link_error.link_error_type = mce_err->u.link_error_type;
		break;
	case MCE_ERROR_TYPE_UNKNOWN:
	default:
		break;
	}
}