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
struct TYPE_2__ {int max_cqe; } ;
struct rxe_dev {TYPE_1__ attr; } ;
struct rxe_cq {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_warn (char*,int,...) ; 
 int queue_count (int /*<<< orphan*/ ) ; 

int rxe_cq_chk_attr(struct rxe_dev *rxe, struct rxe_cq *cq,
		    int cqe, int comp_vector)
{
	int count;

	if (cqe <= 0) {
		pr_warn("cqe(%d) <= 0\n", cqe);
		goto err1;
	}

	if (cqe > rxe->attr.max_cqe) {
		pr_warn("cqe(%d) > max_cqe(%d)\n",
			cqe, rxe->attr.max_cqe);
		goto err1;
	}

	if (cq) {
		count = queue_count(cq->queue);
		if (cqe < count) {
			pr_warn("cqe(%d) < current # elements in queue (%d)",
				cqe, count);
			goto err1;
		}
	}

	return 0;

err1:
	return -EINVAL;
}