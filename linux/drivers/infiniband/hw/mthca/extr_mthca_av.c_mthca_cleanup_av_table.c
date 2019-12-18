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
struct TYPE_2__ {int /*<<< orphan*/  alloc; int /*<<< orphan*/  pool; scalar_t__ av_map; } ;
struct mthca_dev {TYPE_1__ av_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  mthca_alloc_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 

void mthca_cleanup_av_table(struct mthca_dev *dev)
{
	if (mthca_is_memfree(dev))
		return;

	if (dev->av_table.av_map)
		iounmap(dev->av_table.av_map);
	dma_pool_destroy(dev->av_table.pool);
	mthca_alloc_cleanup(&dev->av_table.alloc);
}