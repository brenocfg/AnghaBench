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
struct sdio_func {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int EINVAL ; 
 int mmc_io_rw_direct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned char*) ; 

unsigned char sdio_f0_readb(struct sdio_func *func, unsigned int addr,
	int *err_ret)
{
	int ret;
	unsigned char val;

	if (!func) {
		if (err_ret)
			*err_ret = -EINVAL;
		return 0xFF;
	}

	ret = mmc_io_rw_direct(func->card, 0, 0, addr, 0, &val);
	if (err_ret)
		*err_ret = ret;
	if (ret)
		return 0xFF;

	return val;
}