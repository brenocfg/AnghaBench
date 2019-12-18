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
typedef  scalar_t__ u64 ;
struct sky2_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ gma_read64 (struct sky2_hw*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline u64 get_stats64(struct sky2_hw *hw, unsigned port, unsigned reg)
{
	u64 val;

	do {
		val = gma_read64(hw, port, reg);
	} while (gma_read64(hw, port, reg) != val);

	return val;
}