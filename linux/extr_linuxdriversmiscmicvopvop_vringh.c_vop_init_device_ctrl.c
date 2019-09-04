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
struct vop_vdev {struct mic_device_ctrl* dc; } ;
struct mic_device_desc {int dummy; } ;
struct mic_device_ctrl {int c2h_vdev_db; int h2c_vdev_db; scalar_t__ used_address_updated; scalar_t__ host_ack; scalar_t__ vdev_reset; scalar_t__ guest_ack; scalar_t__ config_change; } ;

/* Variables and functions */
 int mic_aligned_desc_size (struct mic_device_desc*) ; 

__attribute__((used)) static void vop_init_device_ctrl(struct vop_vdev *vdev,
				 struct mic_device_desc *devpage)
{
	struct mic_device_ctrl *dc;

	dc = (void *)devpage + mic_aligned_desc_size(devpage);

	dc->config_change = 0;
	dc->guest_ack = 0;
	dc->vdev_reset = 0;
	dc->host_ack = 0;
	dc->used_address_updated = 0;
	dc->c2h_vdev_db = -1;
	dc->h2c_vdev_db = -1;
	vdev->dc = dc;
}