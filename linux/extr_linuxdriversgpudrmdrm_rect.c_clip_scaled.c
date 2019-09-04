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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;

/* Variables and functions */
 int DIV_ROUND_DOWN_ULL (int /*<<< orphan*/ ,int) ; 
 int DIV_ROUND_UP_ULL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mul_u32_u32 (int,int) ; 

__attribute__((used)) static u32 clip_scaled(u32 src, u32 dst, u32 clip)
{
	u64 tmp = mul_u32_u32(src, dst - clip);

	/*
	 * Round toward 1.0 when clipping so that we don't accidentally
	 * change upscaling to downscaling or vice versa.
	 */
	if (src < (dst << 16))
		return DIV_ROUND_UP_ULL(tmp, dst);
	else
		return DIV_ROUND_DOWN_ULL(tmp, dst);
}