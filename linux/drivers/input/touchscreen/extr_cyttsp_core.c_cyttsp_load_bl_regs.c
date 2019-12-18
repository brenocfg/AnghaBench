#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bl_status; } ;
struct cyttsp {TYPE_1__ bl_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CY_REG_BASE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int ttsp_read_block_data (struct cyttsp*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 

__attribute__((used)) static int cyttsp_load_bl_regs(struct cyttsp *ts)
{
	memset(&ts->bl_data, 0, sizeof(ts->bl_data));
	ts->bl_data.bl_status = 0x10;

	return ttsp_read_block_data(ts, CY_REG_BASE,
				    sizeof(ts->bl_data), &ts->bl_data);
}