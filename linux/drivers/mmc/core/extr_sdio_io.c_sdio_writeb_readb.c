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
struct sdio_func {int /*<<< orphan*/  num; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int mmc_io_rw_direct (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,int,int*) ; 

u8 sdio_writeb_readb(struct sdio_func *func, u8 write_byte,
	unsigned int addr, int *err_ret)
{
	int ret;
	u8 val;

	ret = mmc_io_rw_direct(func->card, 1, func->num, addr,
			write_byte, &val);
	if (err_ret)
		*err_ret = ret;
	if (ret)
		return 0xff;

	return val;
}