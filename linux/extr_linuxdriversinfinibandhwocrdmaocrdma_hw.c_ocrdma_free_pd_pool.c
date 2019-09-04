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
struct ocrdma_dev {TYPE_1__* pd_mgr; } ;
struct TYPE_2__ {struct TYPE_2__* pd_dpp_bitmap; struct TYPE_2__* pd_norm_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  ocrdma_mbx_dealloc_pd_range (struct ocrdma_dev*) ; 

__attribute__((used)) static void ocrdma_free_pd_pool(struct ocrdma_dev *dev)
{
	ocrdma_mbx_dealloc_pd_range(dev);
	kfree(dev->pd_mgr->pd_norm_bitmap);
	kfree(dev->pd_mgr->pd_dpp_bitmap);
	kfree(dev->pd_mgr);
}