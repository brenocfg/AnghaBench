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
struct mic_device_ctrl {int /*<<< orphan*/  vdev; } ;
struct _vop_vdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ readq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct _vop_vdev *vop_dc_to_vdev(struct mic_device_ctrl *dc)
{
	return (struct _vop_vdev *)(unsigned long)readq(&dc->vdev);
}