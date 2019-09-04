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
struct ehea_swqe {int /*<<< orphan*/  tx_control; } ;
struct ehea_qp_init_attr {int act_nr_send_wqes; } ;
struct ehea_qp {struct ehea_qp_init_attr init_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHEA_SWQE_PURGE ; 
 struct ehea_swqe* ehea_get_swqe (struct ehea_qp*,int*) ; 

__attribute__((used)) static void ehea_purge_sq(struct ehea_qp *orig_qp)
{
	struct ehea_qp qp = *orig_qp;
	struct ehea_qp_init_attr *init_attr = &qp.init_attr;
	struct ehea_swqe *swqe;
	int wqe_index;
	int i;

	for (i = 0; i < init_attr->act_nr_send_wqes; i++) {
		swqe = ehea_get_swqe(&qp, &wqe_index);
		swqe->tx_control |= EHEA_SWQE_PURGE;
	}
}