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
typedef  int u32 ;
struct mthca_dev {int mthca_flags; } ;

/* Variables and functions */
 int MTHCA_FLAG_SINAI_OPT ; 

__attribute__((used)) static inline u32 adjust_key(struct mthca_dev *dev, u32 key)
{
	if (dev->mthca_flags & MTHCA_FLAG_SINAI_OPT)
		return ((key << 20) & 0x800000) | (key & 0x7fffff);
	else
		return key;
}