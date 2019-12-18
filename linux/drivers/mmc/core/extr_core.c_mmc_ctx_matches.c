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
struct task_struct {int dummy; } ;
struct mmc_host {struct mmc_ctx* claimer; } ;
struct mmc_ctx {struct task_struct* task; } ;

/* Variables and functions */

__attribute__((used)) static inline bool mmc_ctx_matches(struct mmc_host *host, struct mmc_ctx *ctx,
				   struct task_struct *task)
{
	return host->claimer == ctx ||
	       (!ctx && task && host->claimer->task == task);
}