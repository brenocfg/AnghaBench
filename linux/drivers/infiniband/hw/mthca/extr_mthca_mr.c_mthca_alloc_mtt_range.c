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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  mtt_table; } ;
struct mthca_dev {TYPE_1__ mr_table; } ;
struct mthca_buddy {int dummy; } ;

/* Variables and functions */
 int mthca_buddy_alloc (struct mthca_buddy*,int) ; 
 int /*<<< orphan*/  mthca_buddy_free (struct mthca_buddy*,int,int) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 scalar_t__ mthca_table_get_range (struct mthca_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u32 mthca_alloc_mtt_range(struct mthca_dev *dev, int order,
				 struct mthca_buddy *buddy)
{
	u32 seg = mthca_buddy_alloc(buddy, order);

	if (seg == -1)
		return -1;

	if (mthca_is_memfree(dev))
		if (mthca_table_get_range(dev, dev->mr_table.mtt_table, seg,
					  seg + (1 << order) - 1)) {
			mthca_buddy_free(buddy, seg, order);
			seg = -1;
		}

	return seg;
}