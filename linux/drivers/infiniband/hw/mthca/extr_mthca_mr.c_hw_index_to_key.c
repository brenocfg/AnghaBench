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
typedef  int /*<<< orphan*/  u32 ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arbel_hw_index_to_key (int /*<<< orphan*/ ) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  tavor_hw_index_to_key (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 hw_index_to_key(struct mthca_dev *dev, u32 ind)
{
	if (mthca_is_memfree(dev))
		return arbel_hw_index_to_key(ind);
	else
		return tavor_hw_index_to_key(ind);
}