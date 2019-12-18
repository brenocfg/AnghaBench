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
struct ipr_ioa_cfg {TYPE_1__* host; } ;
struct ipr_cmnd {int /*<<< orphan*/  (* done ) (struct ipr_cmnd*) ;struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ipr_cmnd*) ; 

__attribute__((used)) static void ipr_lock_and_done(struct ipr_cmnd *ipr_cmd)
{
	unsigned long lock_flags;
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	ipr_cmd->done(ipr_cmd);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
}