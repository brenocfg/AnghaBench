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
struct mip4_ts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIP4_BOOT_MODE_BOOT ; 
 int mip4_bl_change_mode (struct mip4_ts*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mip4_bl_enter(struct mip4_ts *ts)
{
	return mip4_bl_change_mode(ts, MIP4_BOOT_MODE_BOOT);
}