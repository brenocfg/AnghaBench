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
struct mmc_pwrseq {TYPE_1__* ops; } ;
struct mmc_host {struct mmc_pwrseq* pwrseq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mmc_host*) ; 

void mmc_pwrseq_reset(struct mmc_host *host)
{
	struct mmc_pwrseq *pwrseq = host->pwrseq;

	if (pwrseq && pwrseq->ops->reset)
		pwrseq->ops->reset(host);
}