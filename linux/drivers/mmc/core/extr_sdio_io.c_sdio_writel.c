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
typedef  int /*<<< orphan*/  u32 ;
struct sdio_func {scalar_t__ tmpbuf; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int sdio_memcpy_toio (struct sdio_func*,unsigned int,scalar_t__,int) ; 

void sdio_writel(struct sdio_func *func, u32 b, unsigned int addr, int *err_ret)
{
	int ret;

	*(__le32 *)func->tmpbuf = cpu_to_le32(b);

	ret = sdio_memcpy_toio(func, addr, func->tmpbuf, 4);
	if (err_ret)
		*err_ret = ret;
}