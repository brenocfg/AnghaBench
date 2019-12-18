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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct ucsi_dp {int vdo_size; TYPE_2__ data; int /*<<< orphan*/ * vdo_data; TYPE_1__* alt; } ;
struct TYPE_3__ {int /*<<< orphan*/  vdo; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int DP_CAP_CAPABILITY (int /*<<< orphan*/ ) ; 
 int DP_CAP_DFP_D_PIN_ASSIGN (int /*<<< orphan*/ ) ; 
 int DP_CAP_UFP_D ; 
 int DP_CAP_UFP_D_PIN_ASSIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_PIN_ASSIGN_D ; 
 int /*<<< orphan*/  DP_STATUS_CON_DFP_D ; 
 int /*<<< orphan*/  DP_STATUS_CON_UFP_D ; 
 int /*<<< orphan*/  DP_STATUS_ENABLED ; 
 int /*<<< orphan*/  DP_STATUS_PREFER_MULTI_FUNC ; 

__attribute__((used)) static int ucsi_displayport_status_update(struct ucsi_dp *dp)
{
	u32 cap = dp->alt->vdo;

	dp->data.status = DP_STATUS_ENABLED;

	/*
	 * If pin assignement D is supported, claiming always
	 * that Multi-function is preferred.
	 */
	if (DP_CAP_CAPABILITY(cap) & DP_CAP_UFP_D) {
		dp->data.status |= DP_STATUS_CON_UFP_D;

		if (DP_CAP_UFP_D_PIN_ASSIGN(cap) & BIT(DP_PIN_ASSIGN_D))
			dp->data.status |= DP_STATUS_PREFER_MULTI_FUNC;
	} else {
		dp->data.status |= DP_STATUS_CON_DFP_D;

		if (DP_CAP_DFP_D_PIN_ASSIGN(cap) & BIT(DP_PIN_ASSIGN_D))
			dp->data.status |= DP_STATUS_PREFER_MULTI_FUNC;
	}

	dp->vdo_data = &dp->data.status;
	dp->vdo_size = 2;

	return 0;
}