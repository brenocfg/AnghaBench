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
typedef  int u8 ;
struct b53_device {int /*<<< orphan*/ * vta_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_ARLIO_PAGE ; 
 int EIO ; 
 int VTA_START_CMD ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int b53_do_vlan_op(struct b53_device *dev, u8 op)
{
	unsigned int i;

	b53_write8(dev, B53_ARLIO_PAGE, dev->vta_regs[0], VTA_START_CMD | op);

	for (i = 0; i < 10; i++) {
		u8 vta;

		b53_read8(dev, B53_ARLIO_PAGE, dev->vta_regs[0], &vta);
		if (!(vta & VTA_START_CMD))
			return 0;

		usleep_range(100, 200);
	}

	return -EIO;
}