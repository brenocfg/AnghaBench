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
struct mt9t001 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9T001_OUTPUT_CONTROL_SYNC ; 
 int mt9t001_set_output_control (struct mt9t001*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9t001_ctrl_freeze(struct mt9t001 *mt9t001, bool freeze)
{
	return mt9t001_set_output_control(mt9t001,
		freeze ? 0 : MT9T001_OUTPUT_CONTROL_SYNC,
		freeze ? MT9T001_OUTPUT_CONTROL_SYNC : 0);
}