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
struct TYPE_4__ {int /*<<< orphan*/  alloc; int /*<<< orphan*/  cq; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_cqs; } ;
struct mthca_dev {TYPE_2__ cq_table; TYPE_1__ limits; } ;

/* Variables and functions */
 int /*<<< orphan*/  mthca_alloc_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_array_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mthca_cleanup_cq_table(struct mthca_dev *dev)
{
	mthca_array_cleanup(&dev->cq_table.cq, dev->limits.num_cqs);
	mthca_alloc_cleanup(&dev->cq_table.alloc);
}