#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocrdma_dev {int eq_cnt; TYPE_2__* eq_tbl; } ;
struct TYPE_3__ {int id; } ;
struct TYPE_4__ {TYPE_1__ q; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int ocrdma_get_eq_table_index(struct ocrdma_dev *dev,
		int eqid)
{
	int indx;

	for (indx = 0; indx < dev->eq_cnt; indx++) {
		if (dev->eq_tbl[indx].q.id == eqid)
			return indx;
	}

	return -EINVAL;
}