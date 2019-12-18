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
struct v4l2_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM3560_LED0 ; 
 int lm3560_set_ctrl (struct v4l2_ctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3560_led0_set_ctrl(struct v4l2_ctrl *ctrl)
{
	return lm3560_set_ctrl(ctrl, LM3560_LED0);
}