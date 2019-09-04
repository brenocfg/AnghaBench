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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct tmc_drvdata {scalar_t__ base; struct etr_buf* etr_buf; } ;
struct etr_buf {int full; int /*<<< orphan*/  offset; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sync ) (struct etr_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ TMC_STS ; 
 int TMC_STS_FULL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct etr_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_etr_buf_insert_barrier_packet (struct etr_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_read_rrp (struct tmc_drvdata*) ; 
 int /*<<< orphan*/  tmc_read_rwp (struct tmc_drvdata*) ; 

__attribute__((used)) static void tmc_sync_etr_buf(struct tmc_drvdata *drvdata)
{
	struct etr_buf *etr_buf = drvdata->etr_buf;
	u64 rrp, rwp;
	u32 status;

	rrp = tmc_read_rrp(drvdata);
	rwp = tmc_read_rwp(drvdata);
	status = readl_relaxed(drvdata->base + TMC_STS);
	etr_buf->full = status & TMC_STS_FULL;

	WARN_ON(!etr_buf->ops || !etr_buf->ops->sync);

	etr_buf->ops->sync(etr_buf, rrp, rwp);

	/* Insert barrier packets at the beginning, if there was an overflow */
	if (etr_buf->full)
		tmc_etr_buf_insert_barrier_packet(etr_buf, etr_buf->offset);
}