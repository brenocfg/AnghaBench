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
struct ehea_qp {int /*<<< orphan*/  hw_rqueue1; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_qeit_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ehea_inc_rq1(struct ehea_qp *qp)
{
	hw_qeit_inc(&qp->hw_rqueue1);
}