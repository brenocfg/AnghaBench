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
typedef  int u32 ;
struct gr3d {int /*<<< orphan*/  addr_regs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int GR3D_NUM_REGS ; 
#define  HOST1X_CLASS_GR3D 129 
#define  HOST1X_CLASS_HOST1X 128 
 struct gr3d* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gr3d_is_addr_reg(struct device *dev, u32 class, u32 offset)
{
	struct gr3d *gr3d = dev_get_drvdata(dev);

	switch (class) {
	case HOST1X_CLASS_HOST1X:
		if (offset == 0x2b)
			return 1;

		break;

	case HOST1X_CLASS_GR3D:
		if (offset >= GR3D_NUM_REGS)
			break;

		if (test_bit(offset, gr3d->addr_regs))
			return 1;

		break;
	}

	return 0;
}