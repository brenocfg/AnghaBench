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
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_loop_shutdown_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_loop_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_loop_delete_ctrl_host(struct nvme_ctrl *ctrl)
{
	nvme_loop_shutdown_ctrl(to_loop_ctrl(ctrl));
}