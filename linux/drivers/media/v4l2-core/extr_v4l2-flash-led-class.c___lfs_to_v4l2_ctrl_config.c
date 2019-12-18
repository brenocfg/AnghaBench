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
struct v4l2_ctrl_config {int /*<<< orphan*/  def; int /*<<< orphan*/  step; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct led_flash_setting {int /*<<< orphan*/  val; int /*<<< orphan*/  step; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */

__attribute__((used)) static void __lfs_to_v4l2_ctrl_config(struct led_flash_setting *s,
				struct v4l2_ctrl_config *c)
{
	c->min = s->min;
	c->max = s->max;
	c->step = s->step;
	c->def = s->val;
}