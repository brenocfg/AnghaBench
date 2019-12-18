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
 scalar_t__ SMS_ROT_PHYSICAL_BA (unsigned int) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vrfb_base ; 

__attribute__((used)) static void omap2_sms_write_rot_physical_ba(u32 val, unsigned ctx)
{
	__raw_writel(val, vrfb_base + SMS_ROT_PHYSICAL_BA(ctx));
}