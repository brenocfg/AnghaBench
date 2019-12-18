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
struct st_i2c_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  adap; scalar_t__ base; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ SSC_STA ; 
 int SSC_STA_BUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_recover_bus (int /*<<< orphan*/ *) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int st_i2c_wait_free_bus(struct st_i2c_dev *i2c_dev)
{
	u32 sta;
	int i, ret;

	for (i = 0; i < 10; i++) {
		sta = readl_relaxed(i2c_dev->base + SSC_STA);
		if (!(sta & SSC_STA_BUSY))
			return 0;

		usleep_range(2000, 4000);
	}

	dev_err(i2c_dev->dev, "bus not free (status = 0x%08x)\n", sta);

	ret = i2c_recover_bus(&i2c_dev->adap);
	if (ret) {
		dev_err(i2c_dev->dev, "Failed to recover the bus (%d)\n", ret);
		return ret;
	}

	return -EBUSY;
}