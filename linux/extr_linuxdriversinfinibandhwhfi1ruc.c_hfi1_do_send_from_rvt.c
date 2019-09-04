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
struct rvt_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_do_send (struct rvt_qp*,int) ; 

void hfi1_do_send_from_rvt(struct rvt_qp *qp)
{
	hfi1_do_send(qp, false);
}