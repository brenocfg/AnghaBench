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
struct bnxt_qplib_pd_tbl {scalar_t__ max; int /*<<< orphan*/ * tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_qplib_free_pd_tbl(struct bnxt_qplib_pd_tbl *pdt)
{
	kfree(pdt->tbl);
	pdt->tbl = NULL;
	pdt->max = 0;
}