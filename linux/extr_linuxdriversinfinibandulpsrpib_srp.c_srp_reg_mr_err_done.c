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
struct ib_wc {int dummy; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  srp_handle_qp_err (struct ib_cq*,struct ib_wc*,char*) ; 

__attribute__((used)) static void srp_reg_mr_err_done(struct ib_cq *cq, struct ib_wc *wc)
{
	srp_handle_qp_err(cq, wc, "FAST REG");
}