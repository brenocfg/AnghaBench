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
typedef  int /*<<< orphan*/  uuid_t ;
struct nvmf_ctrl_options {TYPE_1__* host; int /*<<< orphan*/  subsysnqn; } ;
struct nvme_ctrl {scalar_t__ state; TYPE_3__* opts; } ;
struct TYPE_6__ {TYPE_2__* host; int /*<<< orphan*/  subsysnqn; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  nqn; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  nqn; } ;

/* Variables and functions */
 scalar_t__ NVME_CTRL_DEAD ; 
 scalar_t__ NVME_CTRL_DELETING ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
nvmf_ctlr_matches_baseopts(struct nvme_ctrl *ctrl,
			struct nvmf_ctrl_options *opts)
{
	if (ctrl->state == NVME_CTRL_DELETING ||
	    ctrl->state == NVME_CTRL_DEAD ||
	    strcmp(opts->subsysnqn, ctrl->opts->subsysnqn) ||
	    strcmp(opts->host->nqn, ctrl->opts->host->nqn) ||
	    memcmp(&opts->host->id, &ctrl->opts->host->id, sizeof(uuid_t)))
		return false;

	return true;
}