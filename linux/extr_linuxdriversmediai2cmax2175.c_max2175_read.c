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
typedef  int /*<<< orphan*/  u32 ;
struct max2175 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  mxm_err (struct max2175*,char*,int,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max2175_read(struct max2175 *ctx, u8 idx, u8 *val)
{
	u32 regval;
	int ret;

	ret = regmap_read(ctx->regmap, idx, &regval);
	if (ret)
		mxm_err(ctx, "read ret(%d): idx 0x%02x\n", ret, idx);
	else
		*val = regval;

	return ret;
}