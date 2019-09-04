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
struct TYPE_2__ {scalar_t__ max_qp_wr; scalar_t__ max_send_sge; scalar_t__ max_recv_sge; } ;
struct rxe_dev {scalar_t__ max_inline_data; TYPE_1__ attr; } ;
struct ib_qp_cap {scalar_t__ max_send_wr; scalar_t__ max_send_sge; scalar_t__ max_recv_wr; scalar_t__ max_recv_sge; scalar_t__ max_inline_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int rxe_qp_chk_cap(struct rxe_dev *rxe, struct ib_qp_cap *cap,
			  int has_srq)
{
	if (cap->max_send_wr > rxe->attr.max_qp_wr) {
		pr_warn("invalid send wr = %d > %d\n",
			cap->max_send_wr, rxe->attr.max_qp_wr);
		goto err1;
	}

	if (cap->max_send_sge > rxe->attr.max_send_sge) {
		pr_warn("invalid send sge = %d > %d\n",
			cap->max_send_sge, rxe->attr.max_send_sge);
		goto err1;
	}

	if (!has_srq) {
		if (cap->max_recv_wr > rxe->attr.max_qp_wr) {
			pr_warn("invalid recv wr = %d > %d\n",
				cap->max_recv_wr, rxe->attr.max_qp_wr);
			goto err1;
		}

		if (cap->max_recv_sge > rxe->attr.max_recv_sge) {
			pr_warn("invalid recv sge = %d > %d\n",
				cap->max_recv_sge, rxe->attr.max_recv_sge);
			goto err1;
		}
	}

	if (cap->max_inline_data > rxe->max_inline_data) {
		pr_warn("invalid max inline data = %d > %d\n",
			cap->max_inline_data, rxe->max_inline_data);
		goto err1;
	}

	return 0;

err1:
	return -EINVAL;
}