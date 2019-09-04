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
typedef  int /*<<< orphan*/  uint32_t ;
struct qxl_release {int /*<<< orphan*/  release_offset; int /*<<< orphan*/  release_bo; } ;
struct qxl_device {int /*<<< orphan*/  command_ring; } ;
struct qxl_command {int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  qxl_bo_physical_address (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qxl_ring_push (int /*<<< orphan*/ ,struct qxl_command*,int) ; 

int
qxl_push_command_ring_release(struct qxl_device *qdev, struct qxl_release *release,
			      uint32_t type, bool interruptible)
{
	struct qxl_command cmd;

	cmd.type = type;
	cmd.data = qxl_bo_physical_address(qdev, release->release_bo, release->release_offset);

	return qxl_ring_push(qdev->command_ring, &cmd, interruptible);
}