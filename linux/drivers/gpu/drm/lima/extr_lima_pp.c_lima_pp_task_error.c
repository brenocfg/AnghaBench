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
struct lima_sched_pipe {int num_processor; struct lima_ip** processor; } ;
struct lima_ip {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_PP_INT_STATUS ; 
 int /*<<< orphan*/  LIMA_PP_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_pp_hard_reset (struct lima_ip*) ; 
 int /*<<< orphan*/  pp_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lima_pp_task_error(struct lima_sched_pipe *pipe)
{
	int i;

	for (i = 0; i < pipe->num_processor; i++) {
		struct lima_ip *ip = pipe->processor[i];

		dev_err(ip->dev->dev, "pp task error %d int_state=%x status=%x\n",
			i, pp_read(LIMA_PP_INT_STATUS), pp_read(LIMA_PP_STATUS));

		lima_pp_hard_reset(ip);
	}
}