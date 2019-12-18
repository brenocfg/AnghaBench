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
struct max2175 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  max2175_write_bits (struct max2175*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,char*) ; 

__attribute__((used)) static void max2175_i2s_enable(struct max2175 *ctx, bool enable)
{
	if (enable)
		/* Stuff bits are zeroed */
		max2175_write_bits(ctx, 104, 3, 0, 2);
	else
		/* Keep SCK alive */
		max2175_write_bits(ctx, 104, 3, 0, 9);
	mxm_dbg(ctx, "i2s %sabled\n", enable ? "en" : "dis");
}