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
 int max2175_write_bits (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max2175_write_bit(struct max2175 *ctx, u8 idx, u8 bit, u8 newval)
{
	return max2175_write_bits(ctx, idx, bit, bit, newval);
}