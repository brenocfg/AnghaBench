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
typedef  int u32 ;
struct mcp3911 {int dummy; } ;

/* Variables and functions */
 int mcp3911_read (struct mcp3911*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int mcp3911_write (struct mcp3911*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcp3911_update(struct mcp3911 *adc, u8 reg, u32 mask,
		u32 val, u8 len)
{
	u32 tmp;
	int ret;

	ret = mcp3911_read(adc, reg, &tmp, len);
	if (ret)
		return ret;

	val &= mask;
	val |= tmp & ~mask;
	return mcp3911_write(adc, reg, val, len);
}