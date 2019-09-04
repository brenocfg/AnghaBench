#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct TYPE_2__ {int board_flags; } ;

/* Variables and functions */
 int PMAC_MB_CAN_SLEEP ; 
 int PMAC_MB_MAY_SLEEP ; 
 TYPE_1__ pmac_mb ; 

__attribute__((used)) static long
generic_dev_can_wake(struct device_node *node, long param, long value)
{
	/* Todo: eventually check we are really dealing with on-board
	 * video device ...
	 */

	if (pmac_mb.board_flags & PMAC_MB_MAY_SLEEP)
		pmac_mb.board_flags |= PMAC_MB_CAN_SLEEP;
	return 0;
}