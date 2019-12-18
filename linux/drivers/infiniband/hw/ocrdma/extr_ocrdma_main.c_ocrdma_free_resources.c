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
struct ocrdma_dev {int /*<<< orphan*/  cq_tbl; int /*<<< orphan*/  qp_tbl; int /*<<< orphan*/  stag_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocrdma_release_stats_resources (struct ocrdma_dev*) ; 

__attribute__((used)) static void ocrdma_free_resources(struct ocrdma_dev *dev)
{
	ocrdma_release_stats_resources(dev);
	kfree(dev->stag_arr);
	kfree(dev->qp_tbl);
	kfree(dev->cq_tbl);
}