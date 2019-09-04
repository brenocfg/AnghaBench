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
struct radeon_cs_parser {struct evergreen_cs_track* track; } ;
struct evergreen_cs_track {int* reg_safe_bm; } ;

/* Variables and functions */
 int REG_SAFE_BM_SIZE ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool evergreen_is_safe_reg(struct radeon_cs_parser *p, u32 reg)
{
	struct evergreen_cs_track *track = p->track;
	u32 m, i;

	i = (reg >> 7);
	if (unlikely(i >= REG_SAFE_BM_SIZE)) {
		return false;
	}
	m = 1 << ((reg >> 2) & 31);
	if (!(track->reg_safe_bm[i] & m))
		return true;

	return false;
}