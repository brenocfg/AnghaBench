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
struct bfad_s {int /*<<< orphan*/  bfa; } ;
struct bfa_bsg_ioc_stats_s {int /*<<< orphan*/  status; int /*<<< orphan*/  ioc_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_ioc_get_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
bfad_iocmd_ioc_get_stats(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_ioc_stats_s *iocmd = (struct bfa_bsg_ioc_stats_s *)cmd;

	bfa_ioc_get_stats(&bfad->bfa, &iocmd->ioc_stats);
	iocmd->status = BFA_STATUS_OK;
	return 0;
}