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
struct devlink {int dummy; } ;
struct bnxt {struct devlink* dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_dl_params ; 
 int /*<<< orphan*/  devlink_free (struct devlink*) ; 
 int /*<<< orphan*/  devlink_params_unregister (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_unregister (struct devlink*) ; 

void bnxt_dl_unregister(struct bnxt *bp)
{
	struct devlink *dl = bp->dl;

	if (!dl)
		return;

	devlink_params_unregister(dl, bnxt_dl_params,
				  ARRAY_SIZE(bnxt_dl_params));
	devlink_unregister(dl);
	devlink_free(dl);
}