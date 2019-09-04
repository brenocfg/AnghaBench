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
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DEINIT ; 
 int vnic_dev_cmd_status (struct vnic_dev*,int /*<<< orphan*/ ,int*) ; 

int vnic_dev_deinit_done(struct vnic_dev *vdev, int *status)
{
	return vnic_dev_cmd_status(vdev, CMD_DEINIT, status);
}