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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ uwire_base ; 
 int uwire_idx_shift ; 

__attribute__((used)) static inline void uwire_write_reg(int idx, u16 val)
{
	__raw_writew(val, uwire_base + (idx << uwire_idx_shift));
}