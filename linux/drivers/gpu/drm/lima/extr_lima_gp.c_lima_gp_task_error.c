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
struct lima_sched_pipe {struct lima_ip** processor; } ;
struct lima_ip {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_GP_INT_STAT ; 
 int /*<<< orphan*/  LIMA_GP_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gp_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_gp_hard_reset (struct lima_ip*) ; 

__attribute__((used)) static void lima_gp_task_error(struct lima_sched_pipe *pipe)
{
	struct lima_ip *ip = pipe->processor[0];

	dev_err(ip->dev->dev, "gp task error int_state=%x status=%x\n",
		gp_read(LIMA_GP_INT_STAT), gp_read(LIMA_GP_STATUS));

	lima_gp_hard_reset(ip);
}