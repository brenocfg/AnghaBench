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
typedef  int __be32 ;

/* Variables and functions */

__attribute__((used)) static inline bool ip6_mask_is_full(__be32 mask[4])
{
	return !~(mask[0] & mask[1] & mask[2] & mask[3]);
}