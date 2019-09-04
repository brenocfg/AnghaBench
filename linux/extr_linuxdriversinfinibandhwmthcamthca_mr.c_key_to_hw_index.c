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
 int /*<<< orphan*/  arbel_key_to_hw_index (int /*<<< orphan*/ ) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  tavor_key_to_hw_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 key_to_hw_index(struct mthca_dev *dev, u32 key)
{
	if (mthca_is_memfree(dev))
		return arbel_key_to_hw_index(key);
	else
		return tavor_key_to_hw_index(key);
}