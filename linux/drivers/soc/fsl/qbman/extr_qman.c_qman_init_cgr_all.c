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
struct qman_cgr {scalar_t__ cgrid; } ;

/* Variables and functions */
 scalar_t__ CGR_NUM ; 
 int /*<<< orphan*/  QMAN_CGR_FLAG_USE_INIT ; 
 int /*<<< orphan*/  pr_err (char*,int,char*) ; 
 scalar_t__ qm_modify_cgr (struct qman_cgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qman_init_cgr_all(void)
{
	struct qman_cgr cgr;
	int err_cnt = 0;

	for (cgr.cgrid = 0; cgr.cgrid < CGR_NUM; cgr.cgrid++) {
		if (qm_modify_cgr(&cgr, QMAN_CGR_FLAG_USE_INIT, NULL))
			err_cnt++;
	}

	if (err_cnt)
		pr_err("Warning: %d error%s while initialising CGR h/w\n",
		       err_cnt, (err_cnt > 1) ? "s" : "");
}