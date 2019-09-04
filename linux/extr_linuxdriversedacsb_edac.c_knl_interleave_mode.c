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

/* Variables and functions */
 int /*<<< orphan*/  GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u32 knl_interleave_mode(u32 reg)
{
	return GET_BITFIELD(reg, 1, 2);
}