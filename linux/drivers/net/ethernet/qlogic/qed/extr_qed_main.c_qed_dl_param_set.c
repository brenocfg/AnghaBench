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
struct qed_devlink {struct qed_dev* cdev; } ;
struct qed_dev {int /*<<< orphan*/  iwarp_cmt; } ;
struct TYPE_2__ {int /*<<< orphan*/  vbool; } ;
struct devlink_param_gset_ctx {TYPE_1__ val; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 struct qed_devlink* devlink_priv (struct devlink*) ; 

__attribute__((used)) static int qed_dl_param_set(struct devlink *dl, u32 id,
			    struct devlink_param_gset_ctx *ctx)
{
	struct qed_devlink *qed_dl;
	struct qed_dev *cdev;

	qed_dl = devlink_priv(dl);
	cdev = qed_dl->cdev;
	cdev->iwarp_cmt = ctx->val.vbool;

	return 0;
}