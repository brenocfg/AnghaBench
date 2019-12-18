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
typedef  scalar_t__ u64 ;
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ADDR_DEL ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  vdev_neterr (struct vnic_dev*,char*,int /*<<< orphan*/  const*,int) ; 
 int vnic_dev_cmd (struct vnic_dev*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int) ; 

int vnic_dev_del_addr(struct vnic_dev *vdev, const u8 *addr)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;
	int err;
	int i;

	for (i = 0; i < ETH_ALEN; i++)
		((u8 *)&a0)[i] = addr[i];

	err = vnic_dev_cmd(vdev, CMD_ADDR_DEL, &a0, &a1, wait);
	if (err)
		vdev_neterr(vdev, "Can't del addr [%pM], %d\n", addr, err);

	return err;
}