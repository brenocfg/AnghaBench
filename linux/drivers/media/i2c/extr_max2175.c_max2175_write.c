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
struct max2175 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  mxm_err (struct max2175*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max2175_write(struct max2175 *ctx, u8 idx, u8 val)
{
	int ret;

	ret = regmap_write(ctx->regmap, idx, val);
	if (ret)
		mxm_err(ctx, "write ret(%d): idx 0x%02x val 0x%02x\n",
			ret, idx, val);

	return ret;
}