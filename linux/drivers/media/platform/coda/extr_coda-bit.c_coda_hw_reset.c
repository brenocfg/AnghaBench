#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct coda_dev {TYPE_1__* devtype; int /*<<< orphan*/  rstc; int /*<<< orphan*/  coda_mutex; } ;
struct coda_ctx {struct coda_dev* dev; } ;
struct TYPE_2__ {scalar_t__ product; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA9_GDI_BUS_CTRL ; 
 int /*<<< orphan*/  CODA9_GDI_BUS_STATUS ; 
 scalar_t__ CODA_960 ; 
 int /*<<< orphan*/  CODA_REG_BIT_BUSY ; 
 unsigned int CODA_REG_BIT_BUSY_FLAG ; 
 int /*<<< orphan*/  CODA_REG_BIT_CODE_RUN ; 
 int /*<<< orphan*/  CODA_REG_BIT_RUN_INDEX ; 
 unsigned int CODA_REG_RUN_ENABLE ; 
 int ENOENT ; 
 int ETIME ; 
 int coda_read (struct coda_dev*,int /*<<< orphan*/ ) ; 
 int coda_wait_timeout (struct coda_dev*) ; 
 int /*<<< orphan*/  coda_write (struct coda_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int reset_control_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int coda_hw_reset(struct coda_ctx *ctx)
{
	struct coda_dev *dev = ctx->dev;
	unsigned long timeout;
	unsigned int idx;
	int ret;

	lockdep_assert_held(&dev->coda_mutex);

	if (!dev->rstc)
		return -ENOENT;

	idx = coda_read(dev, CODA_REG_BIT_RUN_INDEX);

	if (dev->devtype->product == CODA_960) {
		timeout = jiffies + msecs_to_jiffies(100);
		coda_write(dev, 0x11, CODA9_GDI_BUS_CTRL);
		while (coda_read(dev, CODA9_GDI_BUS_STATUS) != 0x77) {
			if (time_after(jiffies, timeout))
				return -ETIME;
			cpu_relax();
		}
	}

	ret = reset_control_reset(dev->rstc);
	if (ret < 0)
		return ret;

	if (dev->devtype->product == CODA_960)
		coda_write(dev, 0x00, CODA9_GDI_BUS_CTRL);
	coda_write(dev, CODA_REG_BIT_BUSY_FLAG, CODA_REG_BIT_BUSY);
	coda_write(dev, CODA_REG_RUN_ENABLE, CODA_REG_BIT_CODE_RUN);
	ret = coda_wait_timeout(dev);
	coda_write(dev, idx, CODA_REG_BIT_RUN_INDEX);

	return ret;
}