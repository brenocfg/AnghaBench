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
struct sbridge_pvt {int dummy; } ;
typedef  enum dev_type { ____Placeholder_dev_type } dev_type ;

/* Variables and functions */
 int /*<<< orphan*/  GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 
 int __ibridge_get_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum dev_type ibridge_get_width(struct sbridge_pvt *pvt, u32 mtr)
{
	/*
	 * ddr3_width on the documentation but also valid for DDR4 on
	 * Haswell
	 */
	return __ibridge_get_width(GET_BITFIELD(mtr, 7, 8));
}