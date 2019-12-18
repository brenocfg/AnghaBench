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
struct cyttsp {int /*<<< orphan*/  act_dist; } ;
typedef  int /*<<< orphan*/  act_dist_setup ;

/* Variables and functions */
 int /*<<< orphan*/  CY_REG_ACT_DIST ; 
 int ttsp_write_block_data (struct cyttsp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cyttsp_act_dist_setup(struct cyttsp *ts)
{
	u8 act_dist_setup = ts->act_dist;

	/* Init gesture; active distance setup */
	return ttsp_write_block_data(ts, CY_REG_ACT_DIST,
				sizeof(act_dist_setup), &act_dist_setup);
}