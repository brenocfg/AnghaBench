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
struct ace_device {scalar_t__ fsm_continue_flag; int /*<<< orphan*/  fsm_tasklet; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ace_fsm_yield(struct ace_device *ace)
{
	dev_dbg(ace->dev, "ace_fsm_yield()\n");
	tasklet_schedule(&ace->fsm_tasklet);
	ace->fsm_continue_flag = 0;
}