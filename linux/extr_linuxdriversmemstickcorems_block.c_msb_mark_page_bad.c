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
 int /*<<< orphan*/  MEMSTICK_OVERWRITE_PGST0 ; 
 int /*<<< orphan*/  dbg (char*,int,int) ; 
 int /*<<< orphan*/  msb_reset (struct msb_data*,int) ; 
 int msb_set_overwrite_flag (struct msb_data*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msb_mark_page_bad(struct msb_data *msb, int pba, int page)
{
	dbg("marking page %d of pba %d as bad", page, pba);
	msb_reset(msb, true);
	return msb_set_overwrite_flag(msb,
		pba, page, ~MEMSTICK_OVERWRITE_PGST0);
}