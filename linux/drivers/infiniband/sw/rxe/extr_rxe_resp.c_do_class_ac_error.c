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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int status; int goto_error; int /*<<< orphan*/  aeth_syndrome; } ;
struct rxe_qp {TYPE_1__ resp; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;

/* Variables and functions */

__attribute__((used)) static void do_class_ac_error(struct rxe_qp *qp, u8 syndrome,
			      enum ib_wc_status status)
{
	qp->resp.aeth_syndrome	= syndrome;
	qp->resp.status		= status;

	/* indicate that we should go through the ERROR state */
	qp->resp.goto_error	= 1;
}