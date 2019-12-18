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
struct perf_thread {int /*<<< orphan*/  duration; int /*<<< orphan*/  copied; int /*<<< orphan*/  tidx; int /*<<< orphan*/  dma_sync; int /*<<< orphan*/  dma_wait; struct perf_ctx* perf; } ;
struct perf_ctx {TYPE_1__* ntb; int /*<<< orphan*/  tsync; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div64_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_dma ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int perf_sync_test(struct perf_thread *pthr)
{
	struct perf_ctx *perf = pthr->perf;

	if (!use_dma)
		goto no_dma_ret;

	wait_event(pthr->dma_wait,
		   (atomic_read(&pthr->dma_sync) == 0 ||
		    atomic_read(&perf->tsync) < 0));

	if (atomic_read(&perf->tsync) < 0)
		return -EINTR;

no_dma_ret:
	pthr->duration = ktime_sub(ktime_get(), pthr->duration);

	dev_dbg(&perf->ntb->dev, "%d: copied %llu bytes\n",
		pthr->tidx, pthr->copied);

	dev_dbg(&perf->ntb->dev, "%d: lasted %llu usecs\n",
		pthr->tidx, ktime_to_us(pthr->duration));

	dev_dbg(&perf->ntb->dev, "%d: %llu MBytes/s\n", pthr->tidx,
		div64_u64(pthr->copied, ktime_to_us(pthr->duration)));

	return 0;
}