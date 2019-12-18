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
struct siw_qp {int dummy; } ;
struct ib_qp {int dummy; } ;
struct TYPE_2__ {struct siw_qp* qp; } ;

/* Variables and functions */
 TYPE_1__* to_siw_base_qp (struct ib_qp*) ; 

__attribute__((used)) static inline struct siw_qp *to_siw_qp(struct ib_qp *base_qp)
{
	return to_siw_base_qp(base_qp)->qp;
}