#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct tmc_drvdata {TYPE_1__* csdev; scalar_t__ base; struct etr_buf* etr_buf; } ;
struct etr_buf {int full; TYPE_2__* ops; scalar_t__ len; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sync ) (struct etr_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ TMC_STS ; 
 int TMC_STS_FULL ; 
 int TMC_STS_MEMERR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct etr_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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

	/*
	 * If there were memory errors in the session, truncate the
	 * buffer.
	 */
	if (WARN_ON_ONCE(status & TMC_STS_MEMERR)) {
		dev_dbg(&drvdata->csdev->dev,
			"tmc memory error detected, truncating buffer\n");
		etr_buf->len = 0;
		etr_buf->full = 0;
		return;
	}

	etr_buf->full = status & TMC_STS_FULL;

	WARN_ON(!etr_buf->ops || !etr_buf->ops->sync);

	etr_buf->ops->sync(etr_buf, rrp, rwp);
}