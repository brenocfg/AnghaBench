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
typedef  int u64 ;
typedef  int u32 ;
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ADDR_ADD ; 
 int /*<<< orphan*/  CMD_GET_MAC_ADDR ; 
 int /*<<< orphan*/  CMD_INIT ; 
 int CMD_INITF_DEFAULT_MAC ; 
 int /*<<< orphan*/  CMD_INIT_v1 ; 
 scalar_t__ vnic_dev_capable (struct vnic_dev*,int /*<<< orphan*/ ) ; 
 int vnic_dev_cmd (struct vnic_dev*,int /*<<< orphan*/ ,int*,int*,int) ; 

int vnic_dev_init(struct vnic_dev *vdev, int arg)
{
	u64 a0 = (u32)arg, a1 = 0;
	int wait = 1000;
	int r = 0;

	if (vnic_dev_capable(vdev, CMD_INIT))
		r = vnic_dev_cmd(vdev, CMD_INIT, &a0, &a1, wait);
	else {
		vnic_dev_cmd(vdev, CMD_INIT_v1, &a0, &a1, wait);
		if (a0 & CMD_INITF_DEFAULT_MAC) {
			/* Emulate these for old CMD_INIT_v1 which
			 * didn't pass a0 so no CMD_INITF_*.
			 */
			vnic_dev_cmd(vdev, CMD_GET_MAC_ADDR, &a0, &a1, wait);
			vnic_dev_cmd(vdev, CMD_ADDR_ADD, &a0, &a1, wait);
		}
	}
	return r;
}