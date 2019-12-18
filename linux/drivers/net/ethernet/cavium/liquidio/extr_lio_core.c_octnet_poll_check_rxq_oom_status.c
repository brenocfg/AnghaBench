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
struct work_struct {int dummy; } ;
struct octeon_droq {int dummy; } ;
struct octeon_device {struct octeon_droq** droq; } ;
struct lio {struct octeon_device* oct_dev; } ;
struct cavium_wk {int ctxul; scalar_t__ ctxptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_IFSTATE_RUNNING ; 
 int /*<<< orphan*/  ifstate_check (struct lio*,int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_retry_droq_refill (struct octeon_droq*) ; 
 int /*<<< orphan*/  octeon_schedule_rxq_oom_work (struct octeon_device*,struct octeon_droq*) ; 

__attribute__((used)) static void octnet_poll_check_rxq_oom_status(struct work_struct *work)
{
	struct cavium_wk *wk = (struct cavium_wk *)work;
	struct lio *lio = (struct lio *)wk->ctxptr;
	struct octeon_device *oct = lio->oct_dev;
	int q_no = wk->ctxul;
	struct octeon_droq *droq = oct->droq[q_no];

	if (!ifstate_check(lio, LIO_IFSTATE_RUNNING) || !droq)
		return;

	if (octeon_retry_droq_refill(droq))
		octeon_schedule_rxq_oom_work(oct, droq);
}