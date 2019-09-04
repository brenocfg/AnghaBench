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
struct msb_data {int dummy; } ;

/* Variables and functions */
 int MEMSTICK_OVERWRITE_BKST ; 
 int /*<<< orphan*/  msb_reset (struct msb_data*,int) ; 
 int msb_set_overwrite_flag (struct msb_data*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_notice (char*,int) ; 

__attribute__((used)) static int msb_mark_bad(struct msb_data *msb, int pba)
{
	pr_notice("marking pba %d as bad", pba);
	msb_reset(msb, true);
	return msb_set_overwrite_flag(
			msb, pba, 0, 0xFF & ~MEMSTICK_OVERWRITE_BKST);
}