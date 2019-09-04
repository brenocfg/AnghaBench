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
typedef  int /*<<< orphan*/  u8 ;
struct max2175 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  max2175_get_bitval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ max2175_read (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 max2175_read_bits(struct max2175 *ctx, u8 idx, u8 msb, u8 lsb)
{
	u8 val;

	if (max2175_read(ctx, idx, &val))
		return 0;

	return max2175_get_bitval(val, msb, lsb);
}