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
struct rc_dev {struct em28xx_IR* priv; } ;
struct em28xx_IR {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_ir_work ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em28xx_ir_start(struct rc_dev *rc)
{
	struct em28xx_IR *ir = rc->priv;

	INIT_DELAYED_WORK(&ir->work, em28xx_ir_work);
	schedule_delayed_work(&ir->work, 0);

	return 0;
}