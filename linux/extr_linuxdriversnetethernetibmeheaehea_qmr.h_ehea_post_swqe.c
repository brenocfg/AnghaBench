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
struct ehea_swqe {int dummy; } ;
struct ehea_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ehea_update_sqa (struct ehea_qp*,int) ; 
 int /*<<< orphan*/  iosync () ; 

__attribute__((used)) static inline void ehea_post_swqe(struct ehea_qp *my_qp, struct ehea_swqe *swqe)
{
	iosync();
	ehea_update_sqa(my_qp, 1);
}