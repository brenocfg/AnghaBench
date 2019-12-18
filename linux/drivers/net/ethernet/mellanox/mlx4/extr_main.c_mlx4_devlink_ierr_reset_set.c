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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  vbool; } ;
struct devlink_param_gset_ctx {TYPE_1__ val; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_internal_err_reset ; 

__attribute__((used)) static int mlx4_devlink_ierr_reset_set(struct devlink *devlink, u32 id,
				       struct devlink_param_gset_ctx *ctx)
{
	mlx4_internal_err_reset = ctx->val.vbool;
	return 0;
}