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
struct ib_wc {scalar_t__ status; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_WC_SUCCESS ; 
 int /*<<< orphan*/  iser_err_comp (struct ib_wc*,char*) ; 
 scalar_t__ unlikely (int) ; 

void iser_cmd_comp(struct ib_cq *cq, struct ib_wc *wc)
{
	if (unlikely(wc->status != IB_WC_SUCCESS))
		iser_err_comp(wc, "command");
}