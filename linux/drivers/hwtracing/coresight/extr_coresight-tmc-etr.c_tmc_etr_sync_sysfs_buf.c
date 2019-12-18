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
struct tmc_drvdata {struct etr_buf* sysfs_buf; struct etr_buf* etr_buf; } ;
struct etr_buf {int /*<<< orphan*/  offset; scalar_t__ full; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  tmc_etr_buf_insert_barrier_packet (struct etr_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_etr_free_sysfs_buf (struct etr_buf*) ; 
 int /*<<< orphan*/  tmc_sync_etr_buf (struct tmc_drvdata*) ; 

__attribute__((used)) static void tmc_etr_sync_sysfs_buf(struct tmc_drvdata *drvdata)
{
	struct etr_buf *etr_buf = drvdata->etr_buf;

	if (WARN_ON(drvdata->sysfs_buf != etr_buf)) {
		tmc_etr_free_sysfs_buf(drvdata->sysfs_buf);
		drvdata->sysfs_buf = NULL;
	} else {
		tmc_sync_etr_buf(drvdata);
		/*
		 * Insert barrier packets at the beginning, if there was
		 * an overflow.
		 */
		if (etr_buf->full)
			tmc_etr_buf_insert_barrier_packet(etr_buf,
							  etr_buf->offset);
	}
}