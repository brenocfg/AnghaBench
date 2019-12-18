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
struct tmc_drvdata {int dummy; } ;
struct perf_event {int dummy; } ;
struct etr_buf {int dummy; } ;

/* Variables and functions */
 struct etr_buf* alloc_etr_buf (struct tmc_drvdata*,struct perf_event*,int,void**,int) ; 

__attribute__((used)) static struct etr_buf *
get_perf_etr_buf_per_thread(struct tmc_drvdata *drvdata,
			    struct perf_event *event, int nr_pages,
			    void **pages, bool snapshot)
{
	/*
	 * In per-thread mode the etr_buf isn't shared, so just go ahead
	 * with memory allocation.
	 */
	return alloc_etr_buf(drvdata, event, nr_pages, pages, snapshot);
}