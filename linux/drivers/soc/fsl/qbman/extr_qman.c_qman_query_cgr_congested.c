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
struct qman_cgr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cs; } ;
struct qm_mcr_querycgr {TYPE_1__ cgr; } ;

/* Variables and functions */
 int qman_query_cgr (struct qman_cgr*,struct qm_mcr_querycgr*) ; 

int qman_query_cgr_congested(struct qman_cgr *cgr, bool *result)
{
	struct qm_mcr_querycgr query_cgr;
	int err;

	err = qman_query_cgr(cgr, &query_cgr);
	if (err)
		return err;

	*result = !!query_cgr.cgr.cs;
	return 0;
}