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
typedef  int /*<<< orphan*/  u16 ;
struct ocrdma_dev {int /*<<< orphan*/  dev_lock; TYPE_1__* eq_tbl; } ;
struct TYPE_2__ {int cq_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocrdma_get_eq_table_index (struct ocrdma_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocrdma_unbind_eq(struct ocrdma_dev *dev, u16 eq_id)
{
	int i;

	mutex_lock(&dev->dev_lock);
	i = ocrdma_get_eq_table_index(dev, eq_id);
	if (i == -EINVAL)
		BUG();
	dev->eq_tbl[i].cq_cnt -= 1;
	mutex_unlock(&dev->dev_lock);
}