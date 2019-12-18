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
struct TYPE_2__ {int condition; int send_phantom; int single; } ;
struct bnxt_qplib_qp {TYPE_1__ sq; } ;

/* Variables and functions */

__attribute__((used)) static void bnxt_qplib_cancel_phantom_processing(struct bnxt_qplib_qp *qp)
{
	qp->sq.condition = false;
	qp->sq.send_phantom = false;
	qp->sq.single = false;
}