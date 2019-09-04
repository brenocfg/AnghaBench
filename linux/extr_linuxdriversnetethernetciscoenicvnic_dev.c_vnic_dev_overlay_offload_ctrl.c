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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_OVERLAY_OFFLOAD_CTRL ; 
 int vnic_dev_cmd (struct vnic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int vnic_dev_overlay_offload_ctrl(struct vnic_dev *vdev, u8 overlay, u8 config)
{
	u64 a0 = overlay;
	u64 a1 = config;
	int wait = 1000;

	return vnic_dev_cmd(vdev, CMD_OVERLAY_OFFLOAD_CTRL, &a0, &a1, wait);
}