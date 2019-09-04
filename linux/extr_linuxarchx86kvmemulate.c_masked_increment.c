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
typedef  scalar_t__ ulong ;

/* Variables and functions */
 int /*<<< orphan*/  assign_masked (scalar_t__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void masked_increment(ulong *reg, ulong mask, int inc)
{
	assign_masked(reg, *reg + inc, mask);
}