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
typedef  unsigned int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CMD_DEV_SPEC ; 
 int vnic_dev_cmd (struct vnic_dev*,int /*<<< orphan*/ ,unsigned int*,unsigned int*,int) ; 

int vnic_dev_spec(struct vnic_dev *vdev, unsigned int offset, unsigned int size,
	void *value)
{
	u64 a0, a1;
	int wait = 1000;
	int err;

	a0 = offset;
	a1 = size;

	err = vnic_dev_cmd(vdev, CMD_DEV_SPEC, &a0, &a1, wait);

	switch (size) {
	case 1: *(u8 *)value = (u8)a0; break;
	case 2: *(u16 *)value = (u16)a0; break;
	case 4: *(u32 *)value = (u32)a0; break;
	case 8: *(u64 *)value = a0; break;
	default: BUG(); break;
	}

	return err;
}