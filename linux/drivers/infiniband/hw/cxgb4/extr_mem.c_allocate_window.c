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
struct c4iw_wr_wait {int dummy; } ;
struct c4iw_rdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_RI_STAG_MW ; 
 int /*<<< orphan*/  T4_STAG_UNSET ; 
 int write_tpt_entry (struct c4iw_rdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct c4iw_wr_wait*) ; 

__attribute__((used)) static int allocate_window(struct c4iw_rdev *rdev, u32 *stag, u32 pdid,
			   struct c4iw_wr_wait *wr_waitp)
{
	*stag = T4_STAG_UNSET;
	return write_tpt_entry(rdev, 0, stag, 0, pdid, FW_RI_STAG_MW, 0, 0, 0,
			       0UL, 0, 0, 0, 0, NULL, wr_waitp);
}