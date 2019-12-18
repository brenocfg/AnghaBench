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
typedef  size_t u64 ;
typedef  int u32 ;
struct work_struct {int dummy; } ;
struct octeon_device {struct cavium_wq* check_db_wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct cavium_wq {TYPE_1__ wk; int /*<<< orphan*/  wq; } ;
struct cavium_wk {size_t ctxul; scalar_t__ ctxptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __check_db_timeout (struct octeon_device*,size_t) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_db_timeout(struct work_struct *work)
{
	struct cavium_wk *wk = (struct cavium_wk *)work;
	struct octeon_device *oct = (struct octeon_device *)wk->ctxptr;
	u64 iq_no = wk->ctxul;
	struct cavium_wq *db_wq = &oct->check_db_wq[iq_no];
	u32 delay = 10;

	__check_db_timeout(oct, iq_no);
	queue_delayed_work(db_wq->wq, &db_wq->wk.work, msecs_to_jiffies(delay));
}