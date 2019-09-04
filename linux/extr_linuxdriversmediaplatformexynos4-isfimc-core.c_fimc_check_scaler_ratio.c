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
struct TYPE_2__ {int /*<<< orphan*/  enabled; } ;
struct fimc_ctx {TYPE_1__ scaler; } ;

/* Variables and functions */
 int EINVAL ; 
 int SCALER_MAX_HRATIO ; 
 int SCALER_MAX_VRATIO ; 
 int /*<<< orphan*/  swap (int,int) ; 

int fimc_check_scaler_ratio(struct fimc_ctx *ctx, int sw, int sh,
			    int dw, int dh, int rotation)
{
	if (rotation == 90 || rotation == 270)
		swap(dw, dh);

	if (!ctx->scaler.enabled)
		return (sw == dw && sh == dh) ? 0 : -EINVAL;

	if ((sw >= SCALER_MAX_HRATIO * dw) || (sh >= SCALER_MAX_VRATIO * dh))
		return -EINVAL;

	return 0;
}