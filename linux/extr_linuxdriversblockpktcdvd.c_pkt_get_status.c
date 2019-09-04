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
struct pktcdvd_device {int /*<<< orphan*/  pkt_dev; TYPE_1__* bdev; } ;
struct pkt_ctrl_command {int /*<<< orphan*/  num_devices; void* pkt_dev; void* dev; int /*<<< orphan*/  dev_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_WRITERS ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  ctl_mutex ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* new_encode_dev (int /*<<< orphan*/ ) ; 
 struct pktcdvd_device* pkt_find_dev_from_minor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pkt_get_status(struct pkt_ctrl_command *ctrl_cmd)
{
	struct pktcdvd_device *pd;

	mutex_lock_nested(&ctl_mutex, SINGLE_DEPTH_NESTING);

	pd = pkt_find_dev_from_minor(ctrl_cmd->dev_index);
	if (pd) {
		ctrl_cmd->dev = new_encode_dev(pd->bdev->bd_dev);
		ctrl_cmd->pkt_dev = new_encode_dev(pd->pkt_dev);
	} else {
		ctrl_cmd->dev = 0;
		ctrl_cmd->pkt_dev = 0;
	}
	ctrl_cmd->num_devices = MAX_WRITERS;

	mutex_unlock(&ctl_mutex);
}