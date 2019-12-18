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
struct sdio_func {int num; int /*<<< orphan*/  card; int /*<<< orphan*/  enable_timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIME ; 
 int /*<<< orphan*/  SDIO_CCCR_IOEx ; 
 int /*<<< orphan*/  SDIO_CCCR_IORx ; 
 unsigned long jiffies ; 
 int mmc_io_rw_direct (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,unsigned char*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_func_id (struct sdio_func*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int sdio_enable_func(struct sdio_func *func)
{
	int ret;
	unsigned char reg;
	unsigned long timeout;

	if (!func)
		return -EINVAL;

	pr_debug("SDIO: Enabling device %s...\n", sdio_func_id(func));

	ret = mmc_io_rw_direct(func->card, 0, 0, SDIO_CCCR_IOEx, 0, &reg);
	if (ret)
		goto err;

	reg |= 1 << func->num;

	ret = mmc_io_rw_direct(func->card, 1, 0, SDIO_CCCR_IOEx, reg, NULL);
	if (ret)
		goto err;

	timeout = jiffies + msecs_to_jiffies(func->enable_timeout);

	while (1) {
		ret = mmc_io_rw_direct(func->card, 0, 0, SDIO_CCCR_IORx, 0, &reg);
		if (ret)
			goto err;
		if (reg & (1 << func->num))
			break;
		ret = -ETIME;
		if (time_after(jiffies, timeout))
			goto err;
	}

	pr_debug("SDIO: Enabled device %s\n", sdio_func_id(func));

	return 0;

err:
	pr_debug("SDIO: Failed to enable device %s\n", sdio_func_id(func));
	return ret;
}