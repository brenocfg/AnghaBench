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
struct ccw1 {int cmd_code; int /*<<< orphan*/  cda; scalar_t__ count; scalar_t__ flags; } ;
struct ccw0 {int cmd_code; int /*<<< orphan*/  cda; scalar_t__ count; scalar_t__ flags; } ;

/* Variables and functions */
 int CCW_CMD_TIC ; 

__attribute__((used)) static void convert_ccw0_to_ccw1(struct ccw1 *source, unsigned long len)
{
	struct ccw0 ccw0;
	struct ccw1 *pccw1 = source;
	int i;

	for (i = 0; i < len; i++) {
		ccw0 = *(struct ccw0 *)pccw1;
		if ((pccw1->cmd_code & 0x0f) == CCW_CMD_TIC) {
			pccw1->cmd_code = CCW_CMD_TIC;
			pccw1->flags = 0;
			pccw1->count = 0;
		} else {
			pccw1->cmd_code = ccw0.cmd_code;
			pccw1->flags = ccw0.flags;
			pccw1->count = ccw0.count;
		}
		pccw1->cda = ccw0.cda;
		pccw1++;
	}
}