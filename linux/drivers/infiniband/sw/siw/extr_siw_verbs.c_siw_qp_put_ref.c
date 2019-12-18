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
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  siw_qp_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_siw_qp (struct ib_qp*) ; 

void siw_qp_put_ref(struct ib_qp *base_qp)
{
	siw_qp_put(to_siw_qp(base_qp));
}