#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qedr_dev {int num_cnq; TYPE_3__* sgid_tbl; TYPE_3__* sb_array; TYPE_3__* cnq_array; int /*<<< orphan*/  cdev; TYPE_2__* ops; scalar_t__ sb_start; int /*<<< orphan*/  iwarp_wq; } ;
struct TYPE_7__ {int /*<<< orphan*/  pbl; } ;
struct TYPE_6__ {TYPE_1__* common; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* chain_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ IS_IWARP (struct qedr_dev*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  qedr_free_mem_sb (struct qedr_dev*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qedr_free_resources(struct qedr_dev *dev)
{
	int i;

	if (IS_IWARP(dev))
		destroy_workqueue(dev->iwarp_wq);

	for (i = 0; i < dev->num_cnq; i++) {
		qedr_free_mem_sb(dev, &dev->sb_array[i], dev->sb_start + i);
		dev->ops->common->chain_free(dev->cdev, &dev->cnq_array[i].pbl);
	}

	kfree(dev->cnq_array);
	kfree(dev->sb_array);
	kfree(dev->sgid_tbl);
}