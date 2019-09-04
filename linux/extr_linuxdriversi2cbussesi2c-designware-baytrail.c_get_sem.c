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
struct dw_i2c_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int PUNIT_SEMAPHORE_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int get_sem_addr (struct dw_i2c_dev*) ; 
 int iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int get_sem(struct dw_i2c_dev *dev, u32 *sem)
{
	u32 addr = get_sem_addr(dev);
	u32 data;
	int ret;

	ret = iosf_mbi_read(BT_MBI_UNIT_PMC, MBI_REG_READ, addr, &data);
	if (ret) {
		dev_err(dev->dev, "iosf failed to read punit semaphore\n");
		return ret;
	}

	*sem = data & PUNIT_SEMAPHORE_BIT;

	return 0;
}